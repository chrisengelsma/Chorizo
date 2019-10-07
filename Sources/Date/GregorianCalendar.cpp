#include "GregorianCalendar.h"

#include <Const/CalendarConstants.h>
#include <Utils/AlmanacConverter.h>

namespace chorizo
{
    const std::string GregorianCalendar::MonthName(int month)
    {
        assert (month > 0 && month < 13);
        return GregorianCalendarConstants::MonthNames[month - 1];
    }

    const std::string GregorianCalendar::WeekDayName(int weekDayNumber)
    {

    }

    GregorianCalendar::GregorianCalendar()
    {
        time_t now = time(0);
        *this = GregorianCalendar(std::localtime(&now));
    }

    GregorianCalendar::GregorianCalendar(const GregorianCalendar& cal)
        :  GregorianCalendar(cal.getYear(), cal.getMonth(), cal.getDay())
    {
    }

    GregorianCalendar::GregorianCalendar(tm* time)
        : GregorianCalendar(time->tm_year, time->tm_mon + 1, time->tm_mday)
    {
    }

    GregorianCalendar::GregorianCalendar(const Almanac& almanac)
        : GregorianCalendar(AlmanacConverter::ToGregorianCalendar(almanac))
    {
    }

    GregorianCalendar::GregorianCalendar(const int& year, const int& month, const int& day)
        : m_year(year), m_month(month), m_day(day)
    {
        m_julianDay = AlmanacConverter::ToJulianDay(*this);
    }

    std::string GregorianCalendar::getMonthName() const
    {
        return MonthName(m_month);
    }

    std::string GregorianCalendar::getWeekDay() const
    {
        return WeekDayName(getWeekDayNumber());
    }

    std::string GregorianCalendar::getName() const
    {
        return "Gregorian Calendar";
    }

    std::string GregorianCalendar::getDateString() const
    {
        return getMonthName() + " " + std::to_string(getDay()) + ", " + std::to_string(getYear());
    }
}
