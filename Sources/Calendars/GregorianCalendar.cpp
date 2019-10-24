#include "GregorianCalendar.h"

#ifndef CHORIZO_CONVERTER_H_
#include <Utils/Converter.h>
#endif

namespace chorizo
{
    //////////////////////////////////////////////////////////////////////////
    // statics

    const bool GregorianCalendar::IsLeapYear(const int& year, const bool& proleptic)
    {
        auto epoch = GregorianCalendar(Epoch);
        auto date  = GregorianCalendar(year, 1, 1);

        if (proleptic && (date<epoch))
        {
            return JulianCalendar::IsLeapYear(year);
        }

        auto absYear = std::abs(year);

        if (absYear % 4 == 0)
        {
            if (absYear % 400 == 0) return true;
            return absYear % 100 != 0;
        }
        return false;
    }

    const uint32_t GregorianCalendar::DaysInMonth(const int& year, const int& month)
    {
        switch (month)
        {
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                return (GregorianCalendar::IsLeapYear(year)) ? 29 : 28;
            default:
                return 31;
        }
    }

    const std::vector<uint32_t> GregorianCalendar::MonthLengths(const int& year)
    {
        std::vector<uint32_t> days(12);

        for (uint32_t i = 0; i<12; ++i)
        {
            days[i] = GregorianCalendar::DaysInMonth(year, i + 1);
        }

        return days;
    }


    // end statics
    //////////////////////////////////////////////////////////////////////////

    GregorianCalendar::GregorianCalendar()
        : JulianCalendar()
    {
    }

    GregorianCalendar::GregorianCalendar(const double& jday)
        : JulianCalendar(jday)
    {
    }

    GregorianCalendar::GregorianCalendar(const GregorianCalendar& cal)
        : JulianCalendar(cal)
    {
        updateInternal();
    }

    GregorianCalendar::GregorianCalendar(const int& year, const int& month, const int& day)
        : Calendar()
    {
        setYearMonthDay(year, month, day);
    }

    GregorianCalendar::GregorianCalendar(Calendar* cal)
        : Calendar(*cal)
    {
        auto gc = Converter::ToGregorianCalendar(cal);

        m_day   = gc->m_day;
        m_month = gc->m_month;
        m_year  = gc->m_year;
    }

    bool GregorianCalendar::isLeapYear() const
    {
        return GregorianCalendar::IsLeapYear(m_year, true);
    }

    uint32_t GregorianCalendar::getDaysInMonth() const
    {
        return GregorianCalendar::DaysInMonth(m_year, m_month);
    }

    void GregorianCalendar::updateInternal()
    {
        m_jday = Converter::ToJulianDay(this);
    }
}
