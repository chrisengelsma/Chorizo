#include "AlmanacConverter.h"

#include <Date/Almanac.h>
#include <Date/GregorianCalendar.h>

namespace chorizo
{
    double AlmanacConverter::ToJulianDay(const Almanac& almanac)
    {
        try
        {
            auto gregorianCalendar = dynamic_cast<const GregorianCalendar&>(almanac);
            return g2jd(gregorianCalendar);
        }
        catch (const std::bad_cast& bc) { }

        throw (std::bad_cast());
    }

    GregorianCalendar AlmanacConverter::ToGregorianCalendar(const Almanac& almanac)
    {
        try
        {
            auto cal = dynamic_cast<const GregorianCalendar&>(almanac);
            return cal;
        }
        catch (std::bad_cast& bc) {
            return jd2g(ToJulianDay(almanac));
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // private

    double AlmanacConverter::g2jd(const GregorianCalendar& cal)
    {
        int month = cal.getMonth();
        int year = cal.getYear();
        int day = cal.getDay();

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
        return c + day + e + f - 1524.5;
    }

    GregorianCalendar AlmanacConverter::jd2g(const double& jd)
    {
        int J = static_cast<int>(lround(jd + 0.5));
        int y = 4716, j = 1401, m = 2;
        int n = 12, r = 4, p = 1461;
        int v = 3, u = 5, s = 153;
        int w = 2, B = 274277, C = -38;
        int f = J + j + (((4 * J + B) /  146097) * 3) / 4 + C;
        int e = r * f + v;
        int g = (e % p) / r;
        int h = u * g + w;
        int day = (h % s) / u + 1;
        int month = (h / s + m) % n + 1;
        int year = (e / p) - y + (n + m - month) / n;
        return GregorianCalendar(year, month, day);
    }
}
