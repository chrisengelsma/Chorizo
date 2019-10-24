#include "Meeus.h"

namespace chorizo
{
    double Meeus::Equinox(const int& year, const chorizo::Season& season)
    {
        auto jde0 = mean(year, season);
        auto t    = (jde0 - 2451545.0) / 36525.0;
        auto w    = (35999.373 * t) - 2.47;
        auto lam  = 1 + (0.0334 * Maths::Cosd(w)) + (0.0007 * Maths::Cosd(2 * w));

        // Sum periodic terms for time t.
        auto s = 0.0;

        for (auto aTblC : tblC)
        {
            s += aTblC[0] * Maths::Cosd(aTblC[1] + (aTblC[2] * t));
        }

        return jde0 + ((0.00001 * s) / lam);
    }


    double Meeus::DeltaT(const int& year)
    {
        double dt;

        if ((year >= 1620) && (year <= 2000))
        {
            auto i = static_cast<int>((floor((year - 1620) / 2.0)));
            auto f = ((year - 1620) / 2.0) - i;  // Fractional part of year
            dt = deltaTtab[i] + ((deltaTtab[i + 1] - deltaTtab[i]) * f);
        }
        else
        {
            auto t = (year - 2000) / 100.0;
            if (year < 948)
            {
                dt = 2177 + (497 * t) + (44.1 * t * t);
            }
            else
            {
                dt = 102 + (102 * t) + (25.3 * t * t);
                if ((year > 2000) && (year < 2100))
                {
                    dt += 0.37 * (year - 2100);
                }
            }
        }
        return dt;
    }

    double Meeus::EquationOfTime(const double& jd)
    {
        auto tau     = (jd - J2000) / JulianMillennium;
        auto l0      = 280.4664567 + (360007.6982779 * tau) +
                       (0.03032028 * tau * tau) +
                       ((tau * tau * tau) / 49931.0) -
                       (pow(tau, 4) / 15300.0) -
                       (pow(tau, 5) / 2000000.0);
        auto alpha   = SunPosition(jd)[10];
        auto dPsi    = Nutation(jd)[0];
        auto epsilon = ObliquityEquation(jd) + Nutation(jd)[1];

        l0 = Maths::WrapDegrees(l0);

        auto e = l0 + (-0.0057183) - alpha + (dPsi * Maths::Cosd(epsilon));
        e -= 20.0 * (floor(e / 20.0));
        e /= (24 * 60);
        return e;
    }

    double Meeus::ObliquityEquation(const double& jd)
    {
        auto eps = 0.0;
        auto v   = (jd - J2000) / (JulianCentury * 100);
        auto u   = v;
        if (abs(u) < 1.0)
        {
            for (auto oterm : oterms)
            {
                eps += (oterm / 3600.0) * v;
                v *= u;
            }
        }
        return eps;
    }

    double* Meeus::SunPosition(const double& jd)
    {
        auto t          = (jd - J2000) / JulianCentury;
        auto t2         = t * t;
        auto l0         = Maths::WrapDegrees(280.46646 + (36000.76983 * t) + (0.0003032 * t2));
        auto m          = Maths::WrapDegrees(357.52911 + (35999.05029 * t) + (-0.0001537 * t2));
        auto e          = 0.016708634 + (-0.000042037 * t) + (-0.0000001267 * t2);
        auto c          = ((1.914602 + (-0.004817 * t) + (-0.000014 * t2)) * Maths::Sind(m)) +
                          ((0.019993 - (0.000101 * t)) * Maths::Sind(2 * m)) +
                          (0.000289 * Maths::Sind(3 * m));
        auto sunLong    = l0 + c;
        auto sunAnomaly = m + c;
        auto sunRadius  = (1.000001018 * (1 - (e * e))) / (1 + (e * Maths::Cosd(sunAnomaly)));
        auto w          = 125.04 - (1934.136 * t);
        auto lam        = sunLong + (-0.00569) + (-0.00478 * Maths::Cosd(w));
        auto epsilon0   = ObliquityEquation(jd);
        auto epsilon    = epsilon0 + (0.00256 * Maths::Cosd(w));
        auto alpha      = Maths::ToDegrees(atan2(Maths::Cosd(epsilon0) * Maths::Cosd(sunLong), Maths::Cosd(sunLong)));
        auto delta      = Maths::ToDegrees(asin(Maths::Sind(epsilon0) * Maths::Sind(sunLong)));
        auto alphaApp   = Maths::ToDegrees(atan2(Maths::Cosd(epsilon) * Maths::Sind(lam), Maths::Cosd(lam)));
        auto deltaApp   = Maths::ToDegrees(asin(Maths::Sind(epsilon) * Maths::Sind(lam)));

        alpha    = Maths::WrapDegrees(alpha);
        alphaApp = Maths::WrapDegrees(alphaApp);

        return new double[12]{
            l0,          //  [0] Geometric mean longitude of the Sun
            m,           //  [1] mean anomaly of the Sun
            e,           //  [2] Eccentricity of the Earth's orbit
            c,           //  [3] Sun's equation of the center
            sunLong,     //  [4] Sun's true longitude
            sunAnomaly,  //  [5] Sun's true anomaly
            sunRadius,   //  [6] Sun's radius vector in AU
            lam,         //  [7] Sun's apparent longitude at true equinox of date
            alpha,       //  [8] Sun's true right ascension
            delta,       //  [9] Sun's true declination
            alphaApp,    // [10] Sun's apparent right ascension
            deltaApp     // [11] Sun's apparent declination
        };
    }

    double* Meeus::Nutation(const double& jd)
    {
        double dPsi, dEpsilon;
        double dp = 0.0, de = 0.0, ang;
        double ta[5];

        auto t  = (jd - 2451545.0) / (36525.0);
        auto t2 = t * t;
        auto t3 = t2 * t;

        ta[0] = Maths::ToRadians(297.850363 + 445267.111480 * t - 0.0019142 * t2 + t3 / 189474.0);
        ta[1] = Maths::ToRadians(357.527720 + 35999.050340 * t - 0.0001603 * t2 - t3 / 300000.0);
        ta[2] = Maths::ToRadians(134.962980 + 477198.867398 * t + 0.0086972 * t2 + t3 / 56250.0);
        ta[3] = Maths::ToRadians(93.271910 + 483202.017538 * t - 0.0036825 * t2 + t3 / 327170.0);
        ta[4] = Maths::ToRadians(125.044520 - 1934.136261 * t + 0.0020708 * t2 + t3 / 450000.0);

        for (auto i : ta)
        {
            Maths::WrapRadians(i);
        }

        auto to10 = t / 10.0;

        for (size_t i = 0; i < 63; ++i)
        {
            ang = 0.0;
            for (int j = 0; j < 5; ++j)
            {
                int k = i * 5 + j;
                if (nutArgMult[k] != 0)
                { ang += nutArgMult[k] * ta[j]; }
            }
            dp += (nutArgCoeff[(i * 4) + 0] + nutArgCoeff[(i * 4) + 1] * to10) * sin(ang);
            de += (nutArgCoeff[(i * 4) + 2] + nutArgCoeff[(i * 4) + 3] * to10) * cos(ang);
        }

        dPsi     = dp / (3600.0 * 10000.0);
        dEpsilon = de / (3600.0 * 10000.0);

        return new double[2]{dPsi, dEpsilon};
    }

    double Meeus::LunarPhase(const double& jd)
    {
        auto t  = (jd - J2000) / JulianCentury;
        auto t2 = t * t;
        auto t3 = t2 * t;
        auto t4 = t3 * t;

        // Moon mean elongation D
        auto d = 297.8502042 +
                 t * 445267.1115168 -
                 t2 * 0.0016300 +
                 t3 / 545868.0 -
                 t4 / 113065000.0;

        // Moon mean anomaly M'
        auto mp = 134.9634114 +
                  t * 477198.8675055 +
                  t2 * 0.0087414 +
                  t3 / 69699.0 -
                  t4 / 14712000.0;

        auto m = 357.5291092 +
                 t * 35999.0502909 -
                 t2 * 0.0001536 +
                 t3 / 24490000.0;

        auto phase = 180.0 - d -
                     6.289 * Maths::Sind(mp) +
                     2.100 * Maths::Sind(m) -
                     1.274 * Maths::Sind(2 * d - mp) -
                     0.658 * Maths::Sind(2 * d) -
                     0.214 * Maths::Sind(2 * mp) -
                     0.110 * Maths::Sind(d);

        return Maths::WrapDegrees(phase);
    }

    double Meeus::LunarIlluminationFromPhase(const double& phase)
    {
        return 100 * (1.0 + Maths::Cosd(phase)) / 2;
    }

    double* Meeus::MoonQuarters(const int& year, const int& month, const int& day)
    {
        auto quarters = new double[4];

        auto k  = floor((year + ((month - 1) + day / 30.0) / 12.0 - 2000) * 12.3685);
        auto t  = k / 1236.85; // Time in Julian centuries since 2000
        auto t2 = t * t;
        auto t3 = t2 * t;
        auto t4 = t3 * t;

        // Sun's mean anomaly M
        auto m = 2.5534 +
                 k * 29.10535669 -
                 t2 * 0.0000218;

        // Moon's mean anomaly M'
        auto mp = 201.5643 +
                  k * 385.81693528 +
                  t2 * 0.0107438 +
                  t3 * 0.00001239 -
                  t3 * 0.00000011;

        auto e = 1 - 0.002516 * t - 0.0000074 * t2;

        // Moon's argument of latitude
        auto f = 160.7108 +
                 k * 390.67050274 -
                 t2 * 0.0016341 -
                 t3 * 0.00000227 * t3 +
                 t4 * 0.000000011;

        auto omega = 124.7746 -
                     k * 1.56375580 +
                     t2 * 0.0020691 +
                     t3 * 0.00000215;

        m     = Maths::WrapDegrees(m);
        mp    = Maths::WrapDegrees(mp);
        f     = Maths::WrapDegrees(f);
        omega = Maths::WrapDegrees(omega);

        // The full planetary arguments list include 14 terms
        // Only using the 7 most significant.
        double args[7] = {
            Maths::WrapDegrees(299.77 + 0.107408 * k - 0.009173 * t2),
            Maths::WrapDegrees(251.88 + 0.016321 * k),
            Maths::WrapDegrees(251.83 + 26.651886 * k),
            Maths::WrapDegrees(349.42 + 36.412478 * k),
            Maths::WrapDegrees(84.88 + 18.206239 * k),
            Maths::WrapDegrees(141.74 + 53.303771 * k),
            Maths::WrapDegrees(207.14 + 2.453732 * k)
        };

        double jde0 = 2451550.09765 +
                      29.530588853 * k +
                      0.0001337 * t2 -
                      0.000000150 * t3 +
                      0.00000000073 * t4;
        jde0 -= 58.184 / (24.0 * 60.0 * 60.0);

        auto   cnfq = new double[16];
        double coeffA, coeffB;
        double adj;
        double jde;

        for (int iq = 0; iq < 4; ++iq)
        {

            cnfq   = computeLunarCoefficients(iq, m, mp, f, omega, e);
            coeffA = 0;
            coeffB = 0;

            // Quarter adjustment.
            adj = 0.00306 -
                  0.00038 * e * Maths::Cosd(m) +
                  0.00026 * Maths::Cosd(mp) -
                  0.00002 * Maths::Cosd(mp - m) +
                  0.00002 * Maths::Cosd(mp + m) +
                  0.00002 * Maths::Cosd(2 * f);

            jde = jde0 + (29.530588853 * (iq * 0.25));

            for (int i = 0; i < 16; ++i)
            {
                coeffA += tblMoonA[iq][i] * cnfq[i];
            }

            jde += coeffA;

            if (iq == 1)
            {
                jde += adj;
            }

            if (iq == 3)
            {
                jde -= adj;
            }

            for (int i = 0; i < 7; ++i)
            {
                coeffB += tblMoonB[i] * Maths::Sind(args[i]);
            }

            quarters[iq] = jde + coeffB;

            m     = Maths::WrapDegrees(m + 29.10535669 * 0.25);
            mp    = Maths::WrapDegrees(mp + 385.81693528 * 0.25);
            f     = Maths::WrapDegrees(f + 390.67050274 * 0.25);
            omega = Maths::WrapDegrees(omega - 1.56375580 * 0.25);

            args[0] = Maths::WrapDegrees(args[0] + 0.1074080 * 0.25);
            args[1] = Maths::WrapDegrees(args[1] + 0.0163210 * 0.25);
            args[2] = Maths::WrapDegrees(args[2] + 26.651886 * 0.25);
            args[3] = Maths::WrapDegrees(args[3] + 36.412478 * 0.25);
            args[4] = Maths::WrapDegrees(args[4] + 18.206239 * 0.25);
            args[5] = Maths::WrapDegrees(args[5] + 53.303771 * 0.25);
            args[6] = Maths::WrapDegrees(args[6] + 2.4537320 * 0.25);
        }

        delete[] cnfq;
        cnfq = nullptr;

        return quarters;
    }

    //////////////////////////////////////////////////////////////////////////
    // private

    double* Meeus::computeLunarCoefficients(
        const int& quarter, const double& m,
        const double& mp, const double& f,
        const double& omega, const double& e)
    {
        double c01 = Maths::Sind(mp);
        double c02 = Maths::Sind(m);
        double c03 = Maths::Sind(2 * mp);
        double c04 = Maths::Sind(2 * f);
        double c05 = Maths::Sind(mp - m);
        double c06 = Maths::Sind(mp + m);
        double c07 = Maths::Sind(2 * m);
        double c08 = Maths::Sind(mp - 2 * f);
        double c09 = Maths::Sind(mp + 2 * f);
        double c10 = Maths::Sind(2 * mp + m);
        double c11 = Maths::Sind(3 * mp);
        double c12 = Maths::Sind(m + 2 * f);
        double c13 = Maths::Sind(m - 2 * f);
        double c14 = Maths::Sind(2 * mp - m);
        double c15 = Maths::Sind(omega);
        double c16 = Maths::Sind(mp + 2 * m);

        // Coefficients for new and full moons.
        if (quarter % 2 == 0)
        {
            return new double[16]{
                c01, e * c02, c03, c04,
                e * c05, e * c06, e * e * c07, c08,
                c09, e * c10, c11, e * c12,
                e * c13, e * c14, c15, c16};
        }
        else
        {
            return new double[16]{
                c01, e * c02, e * c06, c03,
                c04, e * c05, e * e * c07, c08,
                c09, c11, e * c14, e * c12,
                e * c13, e * e * c16, e * c10, c15
            };
        }
    }

    double Meeus::calculateJde0(const double* series, const double& y)
    {
        double y2 = y * y;
        double y3 = y2 * y;
        double y4 = y3 * y;
        return series[0] +
               (series[1] * y) +
               (series[2] * y2) +
               (series[3] * y3) +
               (series[4] + y4);
    }

    double Meeus::mean(const int& year, const Season& season)
    {
        double y, jde0;
        if (year < 1000)
        {
            y    = year / 1000.0;
            jde0 = calculateJde0(tblA[season], y);
        }
        else
        {
            y    = (year - 2000.0) / 1000.0;
            jde0 = calculateJde0(tblB[season], y);
        }

        return jde0;
    }

    //////////////////////////////////////////////////////////////////////////
    // constants

    const double Meeus::J2000                = 2451545.0;
    const double Meeus::JulianCentury        = 36525.0;
    const double Meeus::JulianMillennium      = (Meeus::JulianCentury * 10);
    const double Meeus::AstronomicalUnit     = 149597870.0;
    const double Meeus::TropicalYear         = 365.24219878;
    const double Meeus::EclipticLongEpoch    = 278.833540;
    const double Meeus::EclipticLongPerigree = 282.596403;

    const double Meeus::tblMoonA[4][16] = {
        {
            -0.40720, 0.17241, 0.01608,  0.01039,
            0.00739, -0.00514, 0.00208, -0.00111,
            -0.00057, 0.00056,  -0.00042, 0.00042,
            0.00038, -0.00024, -0.00017, -0.00007
        },
        {
            -0.62801, 0.17172, -0.01183, 0.00862,
            0.00804, 0.00454,  0.00204, -0.00180,
            -0.00070, -0.00040, -0.00034, 0.00032,
            0.00032, -0.00028, 0.00027,  -0.00017
        },
        {
            -0.40614, 0.17302, 0.01614,  0.01043,
            0.00734, -0.00515, 0.00209, -0.00111,
            -0.00057, 0.00056,  -0.00042, 0.00042,
            0.00038, -0.00024, -0.00017, -0.00007
        },
        {
            -0.62801, 0.17172, -0.01183, 0.00862,
            0.00804, 0.00454,  0.00204, -0.00180,
            -0.00070, -0.00040, -0.00034, 0.00032,
            0.00032, -0.00028, 0.00027,  -0.00017},
    };

    const double Meeus::tblMoonB[7] = {
        0.000325, 0.000165, 0.000164, 0.000126, 0.000110, 0.000062, 0.000060
    };

    const double Meeus::tblA[4][5] = {
        {1721139.29189, 365242.13740, 0.06134,  0.00111,  -0.00071},
        {1721233.25401, 365241.72562, -0.05323, 0.00907,  0.00025},
        {1721325.70455, 365242.49558, -0.11677, -0.00297, 0.00074},
        {1721414.39987, 365242.88257, -0.00769, -0.00933, -0.00006}
    };

    const double Meeus::tblB[4][5]  = {
        {2451623.80984, 365242.37404, 0.05169,  -0.00411, -0.00057},
        {2451716.56767, 365241.62603, 0.00325,  0.00888,  -0.00030},
        {2451810.21715, 365242.01767, -0.11575, 0.00337,  0.00078},
        {2451900.05952, 365242.74049, -0.06223, -0.00823, 0.00032}
    };
    const double Meeus::tblC[24][4] = {
        {485.0, 324.96, 1934.136},
        {203.0, 337.23, 32964.467},
        {199.0, 342.08, 20.186},
        {182.0, 27.85,  445267.112},
        {156.0, 73.14,  45036.886},
        {136.0, 171.52, 22518.443},
        {77.0,  222.54, 65928.934},
        {74.0,  296.72, 3034.906},
        {70.0,  243.58, 9037.513},
        {58.0,  119.81, 33718.147},
        {52.0,  297.17, 150.678},
        {50.0,  21.02,  2281.226},
        {45.0,  247.54, 29929.562},
        {44.0,  325.15, 31555.956},
        {29.0,  60.93,  4443.417},
        {18.0,  155.12, 67555.328},
        {17.0,  288.79, 4562.452},
        {16.0,  198.04, 62894.029},
        {14.0,  199.76, 31436.921},
        {12.0,  95.39,  14577.848},
        {12.0,  287.11, 31931.756},
        {12.0,  320.81, 34777.259},
        {9.0,   227.73, 1222.114},
        {8.0,   15.45,  16859.074}
    };

    const double Meeus::deltaTtab[192] = {
        121.0, 112.0, 103.0, 95.0, 88.0, 82.0, 77.0, 72.0, 68.0, 63.0,
        60.0, 56.0, 53.0, 51.0, 48.0, 46.0, 44.0, 42.0, 40.0, 38.0,
        35.0, 33.0, 31.0, 29.0, 26.0, 24.0, 22.0, 20.0, 18.0, 16.0,
        14.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 7.0, 7.0, 7.0,
        7.0, 7.0, 8.0, 8.0, 9.0, 9.0, 9.0, 9.0, 9.0, 10.0,
        10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 11.0, 11.0, 11.0,
        11.0, 11.0, 12.0, 12.0, 12.0, 12.0, 13.0, 13.0, 13.0, 14.0,
        14.0, 14.0, 14.0, 15.0, 15.0, 15.0, 15.0, 15.0, 16.0, 16.0,
        16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 15.0, 15.0, 14.0, 13.0,
        13.1, 12.5, 12.2, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 11.9,
        11.6, 11.0, 10.2, 9.2, 8.2, 7.1, 6.2, 5.6, 5.4, 5.3,
        5.4, 5.6, 5.9, 6.2, 6.5, 6.8, 7.1, 7.3, 7.5, 7.6,
        7.7, 7.3, 6.2, 5.2, 2.7, 1.4, -1.2, -2.8, -3.8, -4.8,
        -5.5, -5.3, -5.6, -5.7, -5.9, -6.0, -6.3, -6.5, -6.2, -4.7,
        -2.8, -0.1, 2.6, 5.3, 7.7, 10.4, 13.3, 16.0, 18.2, 20.2,
        21.1, 22.4, 23.5, 23.8, 24.3, 24.0, 23.9, 23.9, 23.7, 24.0,
        24.3, 25.3, 26.2, 27.3, 28.2, 29.1, 30.0, 30.7, 31.4, 32.2,
        33.1, 34.0, 35.0, 36.5, 38.3, 40.2, 42.2, 44.5, 46.5, 48.5,
        50.5, 52.2, 53.8, 54.9, 55.8, 56.9, 58.3, 60.0, 61.6, 63.0,
        65.0, 66.6
    };

    // Constants for computing obliquity of the ecliptic.
    const double Meeus::oterms[10] = {
        -4680.93, -1.55, 1999.25, -51.38, -249.67, -39.05, 7.12, 27.87, 5.79, 2.45
    };

    const double Meeus::nutArgMult[315] = {
        0.0, 0.0, 0.0, 0.0, 1.0,
        -2.0, 0.0, 0.0, 2.0, 2.0,
        0.0, 0.0, 0.0, 2.0, 2.0,
        0.0, 0.0, 0.0, 0.0, 2.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        -2.0, 1.0, 0.0, 2.0, 2.0,
        0.0, 0.0, 0.0, 2.0, 1.0,
        0.0, 0.0, 1.0, 2.0, 2.0,
        -2.0, 1.0, 0.0, 2.0, 2.0,
        -2.0, 0.0, 1.0, 0.0, 0.0,
        -2.0, 0.0, 0.0, 2.0, 1.0,
        0.0, 0.0, 1.0, 2.0, 2.0,
        2.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 1.0,
        2.0, 0.0, 1.0, 2.0, 2.0,
        0.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 2.0, 1.0,
        -2.0, 0.0, 2.0, 0.0, 0.0,
        0.0, 0.0, 2.0, 2.0, 1.0,
        2.0, 0.0, 0.0, 2.0, 2.0,
        0.0, 0.0, 2.0, 2.0, 2.0,
        0.0, 0.0, 2.0, 0.0, 0.0,
        -2.0, 0.0, 1.0, 2.0, 2.0,
        0.0, 0.0, 0.0, 2.0, 0.0,
        -2.0, 0.0, 0.0, 2.0, 0.0,
        0.0, 0.0, 1.0, 2.0, 1.0,
        0.0, 2.0, 0.0, 0.0, 0.0,
        2.0, 0.0, 1.0, 0.0, 1.0,
        -2.0, 2.0, 0.0, 2.0, 2.0,
        0.0, 1.0, 0.0, 0.0, 1.0,
        -2.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 0.0, 1.0,
        0.0, 0.0, 2.0, 2.0, 0.0,
        2.0, 0.0, 1.0, 2.0, 1.0,
        2.0, 0.0, 1.0, 2.0, 2.0,
        0.0, 1.0, 0.0, 2.0, 2.0,
        -2.0, 1.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 2.0, 2.0,
        2.0, 0.0, 0.0, 2.0, 1.0,
        2.0, 0.0, 1.0, 0.0, 0.0,
        -2.0, 0.0, 2.0, 2.0, 2.0,
        -2.0, 0.0, 1.0, 2.0, 1.0,
        2.0, 0.0, 2.0, 0.0, 1.0,
        2.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 1.0, 0.0, 0.0,
        -2.0, 1.0, 0.0, 2.0, 1.0,
        -2.0, 0.0, 0.0, 0.0, 1.0,
        0.0, 0.0, 2.0, 2.0, 1.0,
        -2.0, 0.0, 2.0, 0.0, 1.0,
        -2.0, 1.0, 0.0, 2.0, 1.0,
        0.0, 0.0, 1.0, 2.0, 0.0,
        -1.0, 0.0, 1.0, 0.0, 0.0,
        -2.0, 1.0, 0.0, 0.0, 0.0,
        1.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 2.0, 0.0,
        -1.0, 1.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 2.0, 2.0,
        2.0, 1.0, 1.0, 2.0, 2.0,
        0.0, 0.0, 2.0, 2.0, 2.0,
        0.0, 0.0, 3.0, 2.0, 2.0,
        2.0, 1.0, 0.0, 2.0, 2.0
    };

    const double Meeus::nutArgCoeff[315] = {
        -171996.0, -1742.0, 92095.0, 89.0,        /*  0,  0,  0,  0,  1 */
        -13187.0, -16.0, 5736.0, -31.0,        /* -2,  0,  0,  2,  2 */
        -2274.0, -2.0, 977.0, -5.0,        /*  0,  0,  0,  2,  2 */
        2062.0, 2.0, -895.0, 5.0,        /*  0,  0,  0,  0,  2 */
        1426.0, -34.0, 54.0, -1.0,        /*  0,  1,  0,  0,  0 */
        712.0, 1.0, -7.0, 0.0,        /*  0,  0,  1,  0,  0 */
        -517.0, 12.0, 224.0, -6.0,        /* -2,  1,  0,  2,  2 */
        -386.0, -4.0, 200.0, 0.0,        /*  0,  0,  0,  2,  1 */
        -301.0, 0.0, 129.0, -1.0,        /*  0,  0,  1,  2,  2 */
        217.0, -5.0, -95.0, 3.0,        /* -2, -1,  0,  2,  2 */
        -158.0, 0.0, 0.0, 0.0,        /* -2,  0,  1,  0,  0 */
        129.0, 1.0, -70.0, 0.0,        /* -2,  0,  0,  2,  1 */
        123.0, 0.0, -53.0, 0.0,        /*  0,  0, -1,  2,  2 */
        63.0, 0.0, 0.0, 0.0,        /*  2,  0,  0,  0,  0 */
        63.0, 1.0, -33.0, 0.0,        /*  0,  0,  1,  0,  1 */
        -59.0, 0.0, 26.0, 0.0,        /*  2,  0, -1,  2,  2 */
        -58.0, -1.0, 32.0, 0.0,        /*  0,  0, -1,  0,  1 */
        -51.0, 0.0, 27.0, 0.0,        /*  0,  0,  1,  2,  1 */
        48.0, 0.0, 0.0, 0.0,        /* -2,  0,  2,  0,  0 */
        46.0, 0.0, -24.0, 0.0,        /*  0,  0, -2,  2,  1 */
        -38.0, 0.0, 16.0, 0.0,        /*  2,  0,  0,  2,  2 */
        -31.0, 0.0, 13.0, 0.0,        /*  0,  0,  2,  2,  2 */
        29.0, 0.0, 0.0, 0.0,        /*  0,  0,  2,  0,  0 */
        29.0, 0.0, -12.0, 0.0,        /* -2,  0,  1,  2,  2 */
        26.0, 0.0, 0.0, 0.0,        /*  0,  0,  0,  2,  0 */
        -22.0, 0.0, 0.0, 0.0,        /* -2,  0,  0,  2,  0 */
        21.0, 0.0, -10.0, 0.0,        /*  0,  0, -1,  2,  1 */
        17.0, -1.0, 0.0, 0.0,        /*  0,  2,  0,  0,  0 */
        16.0, 0.0, -8.0, 0.0,        /*  2,  0, -1,  0,  1 */
        -16.0, 1.0, 7.0, 0.0,        /* -2,  2,  0,  2,  2 */
        -15.0, 0.0, 9.0, 0.0,        /*  0,  1,  0,  0,  1 */
        -13.0, 0.0, 7.0, 0.0,        /* -2,  0,  1,  0,  1 */
        -12.0, 0.0, 6.0, 0.0,        /*  0, -1,  0,  0,  1 */
        11.0, 0.0, 0.0, 0.0,        /*  0,  0,  2, -2,  0 */
        -10.0, 0.0, 5.0, 0.0,        /*  2,  0, -1,  2,  1 */
        -8.0, 0.0, 3.0, 0.0,        /*  2,  0,  1,  2,  2 */
        7.0, 0.0, -3.0, 0.0,        /*  0,  1,  0,  2,  2 */
        -7.0, 0.0, 0.0, 0.0,        /* -2,  1,  1,  0,  0 */
        -7.0, 0.0, 3.0, 0.0,        /*  0, -1,  0,  2,  2 */
        -7.0, 0.0, 3.0, 0.0,        /*  2,  0,  0,  2,  1 */
        6.0, 0.0, 0.0, 0.0,        /*  2,  0,  1,  0,  0 */
        6.0, 0.0, -3.0, 0.0,        /* -2,  0,  2,  2,  2 */
        6.0, 0.0, -3.0, 0.0,        /* -2,  0,  1,  2,  1 */
        -6.0, 0.0, 3.0, 0.0,        /*  2,  0, -2,  0,  1 */
        -6.0, 0.0, 3.0, 0.0,        /*  2,  0,  0,  0,  1 */
        5.0, 0.0, 0.0, 0.0,        /*  0, -1,  1,  0,  0 */
        -5.0, 0.0, 3.0, 0.0,        /* -2, -1,  0,  2,  1 */
        -5.0, 0.0, 3.0, 0.0,        /* -2,  0,  0,  0,  1 */
        -5.0, 0.0, 3.0, 0.0,        /*  0,  0,  2,  2,  1 */
        4.0, 0.0, 0.0, 0.0,        /* -2,  0,  2,  0,  1 */
        4.0, 0.0, 0.0, 0.0,        /* -2,  1,  0,  2,  1 */
        4.0, 0.0, 0.0, 0.0,        /*  0,  0,  1, -2,  0 */
        -4.0, 0.0, 0.0, 0.0,        /* -1,  0,  1,  0,  0 */
        -4.0, 0.0, 0.0, 0.0,        /* -2,  1,  0,  0,  0 */
        -4.0, 0.0, 0.0, 0.0,        /*  1,  0,  0,  0,  0 */
        3.0, 0.0, 0.0, 0.0,        /*  0,  0,  1,  2,  0 */
        -3.0, 0.0, 0.0, 0.0,        /* -1, -1,  1,  0,  0 */
        -3.0, 0.0, 0.0, 0.0,        /*  0,  1,  1,  0,  0 */
        -3.0, 0.0, 0.0, 0.0,        /*  0, -1,  1,  2,  2 */
        -3.0, 0.0, 0.0, 0.0,        /*  2, -1, -1,  2,  2 */
        -3.0, 0.0, 0.0, 0.0,        /*  0,  0, -2,  2,  2 */
        -3.0, 0.0, 0.0, 0.0,        /*  0,  0,  3,  2,  2 */
        -3.0, 0.0, 0.0, 0.0         /*  2, -1,  0,  2,  2 */
    };

}