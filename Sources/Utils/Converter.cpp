#include "Converter.h"

namespace chorizo
{
    const double Converter::ToJulianDay(const Calendar* cal)
    {
        if (dynamic_cast<const GregorianCalendar*>(cal) != nullptr)
        {
            return g2jd(dynamic_cast<const GregorianCalendar*>(cal));
        }
        else if (dynamic_cast<const JulianCalendar*>(cal) != nullptr)
        {
            return j2jd(dynamic_cast<const JulianCalendar*>(cal));
        }
        else
        {
            return cal->getJulianDay();
        }
    }

    const GregorianCalendar* Converter::ToGregorianCalendar(const Calendar* cal)
    {
        auto gcal = dynamic_cast<const GregorianCalendar*>(cal);
        return (gcal != nullptr) ? gcal : ToGregorianCalendar(cal->getJulianDay());
    }

    const GregorianCalendar* Converter::ToGregorianCalendar(const double& jday)
    {
        return jd2g(jday);
    }

    const JulianCalendar* Converter::ToJulianCalendar(const Calendar* cal)
    {
        auto jcal = dynamic_cast<const JulianCalendar*>(cal);
        return (jcal != nullptr) ? jcal : ToJulianCalendar(cal->getJulianDay());
    }

    const JulianCalendar* Converter::ToJulianCalendar(const double& jday)
    {
        return jd2j(jday);
    }

    /////////////////////////////////////////////////////////////////////////
    // private

    const JulianCalendar* Converter::jd2j(const double& jd)
    {
        int a = std::floor(jd + 0.5);
        int b = a + 1524;
        int c = std::floor((b - 122.10) / 365.25);
        int d = std::floor(365.25 * c);
        int e = std::floor((b - d) / 30.6001);

        int month = static_cast<int>(std::floor((e<14) ? (e - 1) : (e - 13)));
        int year  = static_cast<int>(std::floor((month>2) ? (c - 4716) : c - (4715)));
        int day   = static_cast<int>(b - d - std::floor(30.6001 * e));

        if (year<1)
        {
            year--;
        }

        return new JulianCalendar(year, month, day);
    }

    const GregorianCalendar* Converter::jd2g(const double& jd)
    {
        int J = std::lround(jd + 0.5);
        int y = 4716, j = 1401, m = 2;
        int n = 12, r = 4, p = 1461;
        int v = 3, u = 5, s = 153;
        int w = 2, B = 274277, C = -38;
        int f = J + j + (((4 * J + B) / 146097) * 3) / 4 + C;
        int e = r * f + v;
        int g = (e % p) / r;
        int h = u * g + w;

        int day   = (h % s) / u + 1;
        int month = (h / s + m) % n + 1;
        int year  = (e / p) - y + (n + m - month) / n;
        return new GregorianCalendar(year, month, day);
    }

    const double Converter::j2jd(const JulianCalendar* cal)
    {
        int month = cal->getMonth();
        int year  = cal->getYear();
        int day   = cal->getDay();

        if (year<1)
        {
            year++;
        }
        if (month<=2)
        {
            year--;
            month += 12;
        }

        return static_cast<double>(std::floor(365.25 * (year + 4716))
                                   + std::floor(30.6001 * (month + 1))
                                   + day
                                   - 1524.5);
    }

    const double Converter::g2jd(const GregorianCalendar* cal)
    {
        int month = cal->getMonth();
        int year  = cal->getYear();
        int day   = cal->getDay();
        if (month == 1 || month == 2)
        {
            year--;
            month += 12;
        }
        int a = static_cast<int>(std::floor(year / 100));
        int b = a / 4;
        int c = 2 - a + b;
        int e = static_cast<int>(365.25 * (year + 4716));
        int f = static_cast<int>(30.6001 * (month + 1));
        return static_cast<double>(c + day + e + f - 1524.5);
    }

}