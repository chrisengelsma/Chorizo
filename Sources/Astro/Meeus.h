/**
 * @class chorizo::Meeus
 * @brief Astronomical equations derived by Belgian Astronomer Jean Meeus.
 *
 * @author Chris Engelsma <chris.engelsma@gmail.com>
 * @version 2019.10.7
 */

#ifndef CHORIZO_MEEUS_H_
#define CHORIZO_MEEUS_H_

#ifndef CHORIZO_SEASON_H_
#include <Astro/Season.h>
#endif

#ifndef CHORIZO_MATHS_H_
#include <Utils/Maths.h>
#endif

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif

namespace chorizo
{
    class CHORIZO_EXPORT Meeus
    {
    public:
        static const double J2000;
        static const double JulianCentury;
        static const double JulianMillennium;
        static const double AstronomicalUnit;
        static const double TropicalYear;
        static const double EclipticLongEpoch;
        static const double EclipticLongPerigree;

        // Coefficients for computing lunar quarters
        static const double tblMoonA[4][16];
        static const double tblMoonB[7];
        static const double tblA[4][5]; // For years -1000 to +1000
        static const double tblB[4][5]; // For years +1000 to +3000
        static const double tblC[24][4];
        static const double deltaTtab[192];

        // Constants for computing obliquity of the ecliptic.
        static const double oterms[10];
        static const double nutArgMult[315];
        static const double nutArgCoeff[315];

        /**
         * @brief Calculates the Julian Ephemeris day of an equinox or solstice.
         * @param year      the year.
         * @param season    the season.
         * @return The julian day of the equinox.
         */
        static double Equinox(const int& year, const Season& season);

        /**
         * @brief The difference (in seconds) between Dynamical Time and Universal Time.
         * @param year the year.
         * @return The difference.
         */
        static double DeltaT(const int& year);

        /**
         * @brief The Equation of Time.
         *
         * The equation of time describes the discrepancy between two kinds of solar
         * time: apparent solar time and mean solar time.
         *
         * @param jd The julian day.
         * @return The equation of time as a fraction of a day.
         */
        static double EquationOfTime(const double& jd);

        /**
         * @brief The obliquity of the ecliptic.
         *
         * Calculates the obliquity of the ecliptic for a given julian day. This
         * uses Laskar's 10th degree polynomial fit (J. Laskar, Astronomy and
         * Astrophysics, Vol 157. page 68 [1986]).
         *
         * @param jd A julian day
         * @return the obliquity of the ecliptic.
         */
        static double ObliquityEquation(const double& jd);

        /**
         * @brief The Sun's position.
         *
         * The Sun's position is returned as an array[12], where:
         * array[ 0]  = Geometric mean longitude of the Sun
         * array[ 1]  = Mean anomaly of the Sun
         * array[ 2]  = Eccentricity of the Earth's orbit
         * array[ 3]  = Sun's equation of the center
         * array[ 4]  = Sun's true longitude
         * array[ 5]  = Sun's true anomaly
         * array[ 6]  = Sun's radius vector in AU
         * array[ 7]  = Sun's apparent longitude at true equinox of date
         * array[ 8]  = Sun's true right ascension
         * array[ 9]  = Sun's true declination
         * array[10]  = Sun's apparent right ascension
         * array[11]  = Sun's apparent declination
         *
         * @param jd A julian day.
         * @return the sun's position.
         */
        static double* SunPosition(const double& jd);

        /**
         * @brief Computes the nutation for a given julian day.
         *
         * The nutation is returned as a tuple, where:
         * tuple[0] = The nutation in longitude (delta-Psi)
         * tuple[1] = The nutation in obliquity (delta-Epsilon)
         *
         * @param jd A julian day.
         * @return the nutation.
         */
        static double* Nutation(const double& jd);

        /**
         * @brief Computes the lunar phase (%) of a given julian day.
         *
         * See: Meeus, Chapter 46.
         *
         * @param jd a julian day.
         * @return the lunar phase as a percentage.
         */
        static double LunarPhase(const double& jd);

        /**
         * @brief Gets the lunar illumination as a percentage.
         *
         * Illumination is rounded to the nearest whole percent
         * (e.g. 13.75 => 14%)
         *
         * @param phase a lunar phase.
         * @return the lunar illumination
         */
        static double LunarIlluminationFromPhase(const double& phase);

        /**
         * @brief Gets dates for the next four quarters of the moon.
         *
         * The returned array will begin with the next new moon, followed by
         * the first quarter moon, the full moon, and finally the last
         * quarter moon. The values in the returned array are in
         * julian days.
         *
         * @param year   a year.
         * @param month  a month.
         * @param day    a day.
         * @return       an array[4] containing the next lunar cycle.
         */
        static double* MoonQuarters(const int& year, const int& month, const int& day);

    private:
        static double mean(const int& year, const Season& season);
        static double calculateJde0(const double* series, const double& y);
        static double* computeLunarCoefficients(const int& quarter, const double& m,
                                                const double& mp, const double& f,
                                                const double& omega, const double& e);
    };
}


#endif // CHORIZO_MEEUS_H_
