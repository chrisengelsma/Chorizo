#include "Calendar.h"

namespace chorizo
{
    Calendar::Calendar()
    {
    }

    Calendar::Calendar(const Calendar& cal)
        : m_jday(cal.m_jday)
    {
    }

    Calendar::Calendar(const double& jday)
        : m_jday(jday)
    {
    }

    void Calendar::updateInternal()
    {
    }

    double Calendar::getJulianDay(const bool& modified, const double& epoch) const
    {
        return (modified) ? m_jday - getEpoch() : m_jday;
    }

    uint32_t Calendar::getWeekDayNumber() const
    {
        return static_cast<unsigned int>(std::floor(m_jday + 1.5)) % getDaysPerWeek();
    }

    std::string Calendar::toString() const
    {
        return getName() + "(" + getDateString() + ")";
    }

    std::ostream& operator<<(std::ostream& stream, const Calendar& a)
    {
        stream << a.toString();
        return stream;
    }

    bool operator>(const Calendar& lhs, const Calendar& rhs)
    {
        return (lhs.m_jday>rhs.m_jday);
    }

    bool operator>=(const Calendar& lhs, const Calendar& rhs)
    {
        return (lhs>rhs || lhs == rhs);
    }

    bool operator<(const Calendar& lhs, const Calendar& rhs)
    {
        return (lhs.m_jday<rhs.m_jday);
    }

    bool operator<=(const Calendar& lhs, const Calendar& rhs)
    {
        return (lhs<rhs || lhs == rhs);
    }

    bool operator==(const Calendar& lhs, const Calendar& rhs)
    {
        return (lhs.m_jday == rhs.m_jday);
    }

    bool operator!=(const Calendar& lhs, const Calendar& rhs)
    {
        return !(lhs == rhs);
    }
}
