#include "GregorianCalendar.h"

#include <Utils/Constants.h>
#include <Utils/Converter.h>

namespace chorizo
{
    //////////////////////////////////////////////////////////////////////////
    // static

    const std::string GregorianCalendar::MonthName(int month)
    {
        assert (month>0 && month<13);
        return GregorianCalendarConstants::MonthNames[month - 1];
    }

    const std::string GregorianCalendar::WeekDayName(int weekDayNumber)
    {
        assert(weekDayNumber>=0 && weekDayNumber<7);
        return GregorianCalendarConstants::WeekDayNames[weekDayNumber];
    }

    const bool GregorianCalendar::IsLeapYear(const int& year, const bool& proleptic)
    {
        auto epoch = GregorianCalendar(Epoch);
        auto date  = GregorianCalendar(year, 1, 1);

//        if (proleptic && (date < epoch))
//            return JulianCalendar::IsLeapYear(year);

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
            days[i] = GregorianCalendar::DaysInMonth(year, i + 1);
        return days;
    }

    // static
    //////////////////////////////////////////////////////////////////////////

    GregorianCalendar::GregorianCalendar()
    {
        time_t now     = time(nullptr);
        auto   nowTime = std::localtime(&now);

        m_day   = nowTime->tm_mday;
        m_month = nowTime->tm_mon + 1;
        m_year  = nowTime->tm_year;
    }

    GregorianCalendar::GregorianCalendar(const GregorianCalendar& cal)
        : m_day(cal.m_day),
          m_month(cal.m_month),
          m_year(cal.m_year)
    {
        m_jday = cal.m_jday;
    }

    GregorianCalendar::GregorianCalendar(Calendar* a)
    {
        m_jday = a->getJulianDay();

        auto cal = Converter::ToGregorianCalendar(a);

        m_day   = cal->m_day;
        m_month = cal->m_month;
        m_year  = cal->m_year;
    }

    GregorianCalendar::GregorianCalendar(const double& jday)
    {
        m_jday = jday;
        updateInternal();
    }

    GregorianCalendar::GregorianCalendar(const int& year, const int& month, const int& day)
        : m_year(year),
          m_month(month),
          m_day(day)
    {
        updateInternal();
    }

    void GregorianCalendar::setDay(const int& day)
    {
        if (m_day != day)
            m_day = day;

        updateInternal();
    }

    void GregorianCalendar::setMonth(const int& month)
    {
        if (m_month != month)
            m_month = month;

        updateInternal();
    }

    void GregorianCalendar::setYear(const int& year)
    {
        if (m_year != year)
            m_year = year;

        updateInternal();
    }

    bool GregorianCalendar::isLeapYear() const
    {
        return GregorianCalendar::IsLeapYear(m_year, true);
    }

    std::string GregorianCalendar::getMonthName() const
    {
        return GregorianCalendar::MonthName(m_month);
    }

    std::string GregorianCalendar::getWeekDayName() const
    {
        return GregorianCalendar::WeekDayName(getWeekDayNumber());
    }

    std::string GregorianCalendar::getDateString() const
    {
        return getMonthName() + " " + std::to_string(getDay()) + ", " + std::to_string(getYear());
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
