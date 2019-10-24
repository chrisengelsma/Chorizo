#include "JulianCalendar.h"

#ifndef CHORIZO_CONVERTER_H_
#include <Utils/Converter.h>
#endif

namespace chorizo
{
    //////////////////////////////////////////////////////////////////////////
    // statics

    const std::string JulianCalendar::MonthName(int month)
    {
        assert (month>0 && month<13);
        return Constants().get(Constants::MonthNames, Constants::JulianCalendar, month - 1);
    }

    const std::string JulianCalendar::WeekDayName(int weekDayNumber)
    {
        assert(weekDayNumber>=0 && weekDayNumber<7);
        return Constants().get(Constants::WeekDayNames, Constants::JulianCalendar, weekDayNumber);
    }

    const bool JulianCalendar::IsLeapYear(const int& year)
    {
        return year % 4 == 0;
    }

    const uint32_t JulianCalendar::DaysInMonth(const int& year, const int& month)
    {
        switch (month)
        {
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                return (JulianCalendar::IsLeapYear(year)) ? 29 : 28;
            default:
                return 31;
        }
    }

    const std::vector<uint32_t> JulianCalendar::MonthLengths(const int& year)
    {
        std::vector<uint32_t> days(12);

        for (uint32_t i = 0; i<12; ++i)
            days[i] = JulianCalendar::DaysInMonth(year, i + 1);
        return days;
    }

    // end statics
    //////////////////////////////////////////////////////////////////////////

    JulianCalendar::JulianCalendar()
        : Calendar()
    {
        time_t now     = time(nullptr);
        auto   nowTime = std::localtime(&now);

        m_day   = nowTime->tm_mday;
        m_month = nowTime->tm_mon + 1;
        m_year  = nowTime->tm_year;
    }

    JulianCalendar::JulianCalendar(const JulianCalendar& cal)
        : Calendar(cal),
          m_day(cal.m_day),
          m_month(cal.m_month),
          m_year(cal.m_year)
    {
    }

    JulianCalendar::JulianCalendar(Calendar* cal)
        : Calendar(*cal)
    {
        auto jc = Converter::ToJulianCalendar(cal);

        m_day   = jc->m_day;
        m_month = jc->m_month;
        m_year  = jc->m_year;
    }

    JulianCalendar::JulianCalendar(const double& jday)
        : Calendar(jday)
    {
        updateInternal();
    }

    JulianCalendar::JulianCalendar(const int& year, const int& month, const int& day)
        : Calendar(),
          m_year(year),
          m_month(month),
          m_day(day)
    {
        updateInternal();
    }

    void JulianCalendar::setDay(const int& day)
    {
        if (m_day != day)
        {
            m_day = day;
            updateInternal();
        }
    }

    void JulianCalendar::setMonth(const int& month)
    {
        if (m_month != month)
        {
            m_month = month;
            updateInternal();
        }
    }

    void JulianCalendar::setYear(const int& year)
    {
        if (m_year != year)
        {
            m_year = year;
            updateInternal();
        }
    }

    void JulianCalendar::setYearMonthDay(const int& year, const int& month, const int& day)
    {
        bool update = false;
        if (m_year != year)
        {
            m_year = year;
            update = true;
        }
        if (m_month != month)
        {
            m_month = month;
            update = true;
        }
        if (m_day != day)
        {
            m_day = day;
            update = true;
        }
        if (update)
        {
            updateInternal();
        }
    }

    bool JulianCalendar::isLeapYear() const
    {
        return JulianCalendar::IsLeapYear(m_year);
    }

    std::string JulianCalendar::getMonthName() const
    {
        return JulianCalendar::MonthName(m_month);
    }

    std::string JulianCalendar::getWeekDayName() const
    {
        return JulianCalendar::WeekDayName(getWeekDayNumber());
    }

    std::string JulianCalendar::getDateString() const
    {
        return getMonthName() + " " + std::to_string(getDay()) + ", " + std::to_string(getYear());
    }

    uint32_t JulianCalendar::getDaysInMonth() const
    {
        return JulianCalendar::DaysInMonth(m_year, m_month);
    }

    void JulianCalendar::updateInternal()
    {
        m_jday = Converter::ToJulianDay(this);
    }

}
