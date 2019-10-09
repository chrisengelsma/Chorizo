#ifndef CHORIZO_ALMANAC_H_
#define CHORIZO_ALMANAC_H_

#include "StdAfx.h"

namespace chorizo
{
    class CHORIZO_EXPORT Almanac
    {
    protected:
        double m_julianDay{};
        std::string m_name{};
        size_t m_daysPerWeek{};
        size_t m_monthsPerYear{};

    public:
        Almanac() = default;
        Almanac(const Almanac& a) = default;

        virtual ~Almanac() = default;

        [[nodiscard]] double getJulianDay();
        [[nodiscard]] double getModifiedJulianDay() { return m_julianDay - Epoch; }

        [[nodiscard]] size_t getNumberOfDaysInAWeek() const { return m_daysPerWeek; }
        [[nodiscard]] size_t getNumberOfMonthsInAYear() const { return m_monthsPerYear; }
        [[nodiscard]] std::string getName() const { return m_name; }

        [[nodiscard]] virtual std::string getDateString() const = 0;
        [[nodiscard]] virtual std::string getWeekDay() const = 0;
        virtual void updateFrom() const = 0;

        [[nodiscard]] int getWeekDayNumber() const;

        Almanac* operator+=(const int& days);
        Almanac* operator-=(const int& days);

        [[nodiscard]] std::string toString() const;
        friend std::ostream& operator<<(std::ostream& stream, const Almanac& a);

        friend bool operator> (const Almanac& lhs, const Almanac& rhs);
        friend bool operator>=(const Almanac& lhs, const Almanac& rhs);
        friend bool operator< (const Almanac& lhs, const Almanac& rhs);
        friend bool operator<=(const Almanac& lhs, const Almanac& rhs);
        friend bool operator==(const Almanac& lhs, const Almanac& rhs);
        friend bool operator!=(const Almanac& lhs, const Almanac& rhs);

    private:
        static constexpr double Epoch = 2400000.5;
    };

}

#endif
