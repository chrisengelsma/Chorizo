#include "Almanac.h"

#include <Utils/AlmanacConverter.h>

namespace chorizo
{
    double Almanac::getJulianDay()
    {
        m_julianDay = AlmanacConverter::ToJulianDay(this);
        return m_julianDay;
    }

    int Almanac::getWeekDayNumber() const
    {
        return static_cast<int>(std::floor(m_julianDay + 1.5)) % getNumberOfDaysInAWeek();
    }

    Almanac* Almanac::operator+=(const int& days)
    {
    }

    Almanac* Almanac::operator-=(const int& days)
    {
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
