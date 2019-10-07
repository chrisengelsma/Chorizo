#include "Almanac.h"

namespace chorizo
{
    Almanac::Almanac(const Almanac& a)
        : Almanac(a.getJulianDay())
    {
    }

    Almanac::Almanac(const double& julianDay)
        : m_julianDay(julianDay)
    {
    }

    double Almanac::getJulianDay() const
    {
        return m_julianDay;
    }

    int Almanac::getWeekDayNumber() const
    {
        return static_cast<int>(std::floor(m_julianDay + 1.5)) % getNumberOfDaysInAWeek();
    }

    int Almanac::getNumberOfDaysInAWeek() const
    {
        return 7;
    }

    std::string Almanac::getWeekDay() const
    {
        return "";
    }

    std::string Almanac::toString() const
    {
        return getName() + "(" + getDateString() + ")";
    }

    std::ostream& operator<<(std::ostream& stream, const Almanac& a)
    {
        stream << a.toString();
        return stream;
    }

    bool operator>(const Almanac& lhs, const Almanac& rhs)
    {
        return (lhs.m_julianDay > rhs.m_julianDay);
    }

    bool operator>=(const Almanac& lhs, const Almanac& rhs)
    {
        return (lhs > rhs || lhs == rhs);
    }

    bool operator<(const Almanac& lhs, const Almanac& rhs)
    {
        return (lhs.m_julianDay < rhs.m_julianDay);
    }

    bool operator<=(const Almanac& lhs, const Almanac& rhs)
    {
        return (lhs < rhs || lhs == rhs);
    }

    bool operator==(const Almanac& lhs, const Almanac& rhs)
    {
        return (lhs.m_julianDay == rhs.m_julianDay);
    }

    bool operator!=(const Almanac& lhs, const Almanac& rhs)
    {
        return !(lhs == rhs);
    }
}
