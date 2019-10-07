#ifndef CHORIZO_ALMANAC_H_
#define CHORIZO_ALMANAC_H_

#include "StdAfx.h"

namespace chorizo
{
    class CHORIZO_EXPORT Almanac
    {
    protected:
        double m_julianDay{};

    public:
        Almanac() = default;
        Almanac(const Almanac& a);
        explicit Almanac(const double& julianDay);

        virtual ~Almanac() = default;

        virtual std::string getName() const = 0;
        virtual std::string getDateString() const = 0;

        double getJulianDay() const;

        std::string toString() const;

        int getWeekDayNumber() const;

        virtual int getNumberOfDaysInAWeek() const;
        virtual std::string getWeekDay() const;

        friend std::ostream& operator<<(std::ostream& stream, const Almanac& a);

        friend bool operator>  (const Almanac& lhs, const Almanac& rhs);
        friend bool operator>= (const Almanac& lhs, const Almanac& rhs);
        friend bool operator<  (const Almanac& lhs, const Almanac& rhs);
        friend bool operator<= (const Almanac& lhs, const Almanac& rhs);
        friend bool operator== (const Almanac& lhs, const Almanac& rhs);
        friend bool operator!= (const Almanac& lhs, const Almanac& rhs);
    };
}

#endif
