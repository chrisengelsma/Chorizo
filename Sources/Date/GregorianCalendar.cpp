#include "GregorianCalendar.h"

#include <Const/CalendarConstants.h>
#include <Utils/AlmanacConverter.h>

namespace chorizo
{
    std::string GregorianCalendar::MonthName(int month)
    {
        assert (month > 0 && month < 13);
        return GregorianCalendarConstants::MonthNames[month - 1];
    }

    std::string GregorianCalendar::WeekDayName(int weekDayNumber)
    {
        assert(weekDayNumber > 0 && weekDayNumber < 7);
        return "hi";
    }

    GregorianCalendar::GregorianCalendar()
    {
        time_t now     = time(nullptr);
        auto   nowTime = std::localtime(&now);

        m_day       = nowTime->tm_mday;
        m_month     = nowTime->tm_mon + 1;
        m_year      = nowTime->tm_year;
        m_julianDay = AlmanacConverter::ToJulianDay(this);
    }

    GregorianCalendar::GregorianCalendar(tm* time)
        : GregorianCalendar(time->tm_year, time->tm_mon + 1, time->tm_mday)
    { }

    GregorianCalendar::GregorianCalendar(Almanac* almanac)
    {
        auto cal = AlmanacConverter::ToGregorianCalendar(almanac);

        m_day       = cal->m_day;
        m_month     = cal->m_month;
        m_year      = cal->m_year;
        m_julianDay = cal->m_julianDay;
    }

    GregorianCalendar::GregorianCalendar(const int& year, const int& month, const int& day)
        : m_year(year), m_month(month), m_day(day)
    {
        m_julianDay = AlmanacConverter::ToJulianDay(this);
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
}
