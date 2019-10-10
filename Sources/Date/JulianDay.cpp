#include "JulianDay.h"

#include <Utils/Converter.h>

namespace chorizo
{

    double JulianDay::getJulianDay(const bool& modified) const
    {
        return (modified) ? m_jday : m_jday - m_epoch;
    }

    void JulianDay::setJulianDay(const double& jday)
    {
        m_jday = jday;
        update();
    }

    uint32_t JulianDay::getDaysPerWeek() const
    {
        return m_daysPerWeek;
    }

    uint32_t JulianDay::getMonthsPerYear() const
    {
        return m_monthsPerYear;
    }

    std::string JulianDay::getName() const
    {
        return m_name;
    }

    uint32_t JulianDay::getWeekDayNumber() const
    {
        return static_cast<unsigned int>(std::floor(m_jday + 1.5)) % getDaysPerWeek();
    }

    JulianDay* JulianDay::operator+=(const int& days)
    {
        m_jday += days;
        update();
        return this;
    }

    JulianDay* JulianDay::operator-=(const int& days)
    {
        m_jday -= days;
        update();
        return this;
    }

    std::string JulianDay::toString() const
    {
        return getName() + "(" + getDateString() + ")";
    }

    std::ostream& operator<<(std::ostream& stream, const JulianDay& a)
    {
        stream << a.toString();
        return stream;
    }

    bool operator>(const JulianDay& lhs, const JulianDay& rhs)
    {
        return (lhs.m_jday > rhs.m_jday);
    }

    bool operator>=(const JulianDay& lhs, const JulianDay& rhs)
    {
        return (lhs > rhs || lhs == rhs);
    }

    bool operator<(const JulianDay& lhs, const JulianDay& rhs)
    {
        return (lhs.m_jday < rhs.m_jday);
    }

    bool operator<=(const JulianDay& lhs, const JulianDay& rhs)
    {
        return (lhs < rhs || lhs == rhs);
    }

    bool operator==(const JulianDay& lhs, const JulianDay& rhs)
    {
        return (lhs.m_jday == rhs.m_jday);
    }

    bool operator!=(const JulianDay& lhs, const JulianDay& rhs)
    {
        return !(lhs == rhs);
    }

    void JulianDay::updateInternal()
    {
        m_jday = Converter::ToJulianDay(this);
    }
}
