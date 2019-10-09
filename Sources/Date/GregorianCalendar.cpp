#include "GregorianCalendar.h"

#include <Helpers/CalendarConstants.h>
#include <Utils/AlmanacConverter.h>

namespace chorizo
{
    std::string GregorianCalendar::MonthName(int month)
    {
        assert (month>0 && month<13);
        return GregorianCalendarConstants::MonthNames[month - 1];
    }

    std::string GregorianCalendar::WeekDayName(int weekDayNumber)
    {
        assert(weekDayNumber>0 && weekDayNumber<7);
        return GregorianCalendarConstants::WeekDayNames[weekDayNumber - 1];
    }

    GregorianCalendar::GregorianCalendar()
    {
        time_t now     = time(nullptr);
        auto   nowTime = std::localtime(&now);

        m_day   = nowTime->tm_mday;
        m_month = nowTime->tm_mon + 1;
        m_year  = nowTime->tm_year;
        m_jday  = AlmanacConverter::ToJulianDay(this);
    }

    GregorianCalendar::GregorianCalendar(const GregorianCalendar& cal)
    : m_day(cal.m_day),
      m_month(cal.m_month),
      m_year(cal.m_year)
    {
        m_jday = cal.m_jday;
    }

    GregorianCalendar::GregorianCalendar(tm* time)
        : GregorianCalendar(time->tm_year, time->tm_mon + 1, time->tm_mday)
    { }

    GregorianCalendar::GregorianCalendar(JulianDay* julianDay)
    {
        auto cal = AlmanacConverter::ToGregorianCalendar(julianDay);

        m_day   = cal->m_day;
        m_month = cal->m_month;
        m_year  = cal->m_year;
        m_jday  = cal->m_jday;
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


    GregorianCalendar::GregorianCalendar(const int& year, const int& month, const int& day)
        : m_year(year), m_month(month), m_day(day)
    {
        m_jday = AlmanacConverter::ToJulianDay(this);
    }

    std::string GregorianCalendar::getMonthName() const
    {
        return MonthName(m_month);
    }

    std::string GregorianCalendar::getWeekDay() const
    {
        return WeekDayName(getWeekDayNumber());
    }

    std::string GregorianCalendar::getDateString() const
    {
        return getMonthName() + " " + std::to_string(getDay()) + ", " + std::to_string(getYear());
    }

    void GregorianCalendar::update()
    {
        auto cal = AlmanacConverter::ToGregorianCalendar(this);
        m_month = cal->getMonth();
        m_day = cal->getDay();
        m_year = cal->getYear();
    }

}
