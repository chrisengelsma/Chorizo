#include "JulianDay.h"

#include <Utils/AlmanacConverter.h>

namespace chorizo
{
    void JulianDay::setJulianDay(const double& jday)
    {
        m_jday = jday;
        update();
    }

    int JulianDay::getWeekDayNumber() const
    {
        return static_cast<int>(std::floor(m_jday + 1.5)) % getNumberOfDaysInAWeek();
    }

    JulianDay* JulianDay::operator+=(const int& days)
    {
        return nullptr;
    }

    JulianDay* JulianDay::operator-=(const int& days)
    {
        return nullptr;
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
        m_jday = AlmanacConverter::ToJulianDay(this);
    }
}
