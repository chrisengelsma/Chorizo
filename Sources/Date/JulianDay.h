#ifndef CHORIZO_JULIANDAY_H_
#define CHORIZO_JULIANDAY_H_

#include "StdAfx.h"

namespace chorizo
{
    class CHORIZO_EXPORT JulianDay
    {
    protected:
        double m_jday{};

        std::string m_name{};
        size_t m_daysPerWeek{};
        size_t m_monthsPerYear{};

    public:
        JulianDay() = default;

        JulianDay(const JulianDay& a) = default;

        virtual ~JulianDay() = 0;

        double getJulianDay() const { return m_jday; }

        void setJulianDay(const double& jday);

        double getModifiedJulianDay() { return m_jday - Epoch; }

        size_t getNumberOfDaysInAWeek() const { return m_daysPerWeek; }

        size_t getNumberOfMonthsInAYear() const { return m_monthsPerYear; }

        std::string getName() const { return m_name; }

        virtual std::string getDateString() const = 0;
        virtual std::string getWeekDay() const = 0;

        int getWeekDayNumber() const;

        JulianDay* operator+=(const int& days);
        JulianDay* operator-=(const int& days);

        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& stream, const JulianDay& a);

        friend bool operator> (const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator>=(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator< (const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator<=(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator==(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator!=(const JulianDay& lhs, const JulianDay& rhs);

    protected:
        virtual void update() = 0;
        void updateInternal();

    private:
        static constexpr double Epoch = 2400000.5;
    };

    inline JulianDay::~JulianDay() {}
}

#endif // CHORIZO_JULIANDAY_H_
