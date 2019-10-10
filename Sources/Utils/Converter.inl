#include "Converter.h"

#include <StdAfx.h>
#include <Date/JulianDay.h>
#include <Date/GregorianCalendar.h>

namespace chorizo
{
    template<typename TFrom, typename TTo>
    TTo* Converter::Convert(TFrom* cal)
    {
        if constexpr (std::is_same<TTo, GregorianCalendar*>::value)
        {
        }

        return cal;
    }

    /*
    double Converter::ToJulianDay(JulianDay* julianDay)
    {
        auto gregorianCalendar = dynamic_cast<GregorianCalendar*>(julianDay);
        if (gregorianCalendar != nullptr)
        {
            return g2jd(gregorianCalendar);
        }
        else
        {
            return julianDay->getJulianDay();
        }
    }

    GregorianCalendar* Converter::ToGregorianCalendar(JulianDay* julianDay)
    {
        return jd2g(julianDay->getJulianDay());
    }

     */
    //////////////////////////////////////////////////////////////////////////
    // private

    double Converter::g2jd(GregorianCalendar* cal)
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
        return c + day + e + f - 1524.5;
    }

    GregorianCalendar* Converter::jd2g(const double& jd)
    {
        int J = static_cast<int>(lround(jd + 0.5));
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
}
