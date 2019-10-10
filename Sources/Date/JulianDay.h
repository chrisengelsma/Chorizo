#ifndef CHORIZO_JULIANDAY_H_
#define CHORIZO_JULIANDAY_H_

#include "StdAfx.h"

namespace chorizo
{
    class CHORIZO_EXPORT JulianDay
    {

    public:
        JulianDay() = default;

        virtual ~JulianDay() = 0;

        virtual std::string getDateString() const = 0;

        virtual std::string getWeekDay() const = 0;

        double getJulianDay(const bool& modified = false) const;

        void setJulianDay(const double& jday);

        uint32_t getDaysPerWeek() const;

        uint32_t getMonthsPerYear() const;

        std::string getName() const;

        uint32_t getWeekDayNumber() const;

        JulianDay* operator+=(const int& days);
        JulianDay* operator-=(const int& days);

        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& stream, const JulianDay& a);

        friend bool operator>(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator>=(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator<(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator<=(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator==(const JulianDay& lhs, const JulianDay& rhs);
        friend bool operator!=(const JulianDay& lhs, const JulianDay& rhs);

    protected:
        double      m_jday{};
        std::string m_name{};
        size_t      m_daysPerWeek{};
        size_t      m_monthsPerYear{};
        double      m_epoch{2400000.5};

        void updateInternal();

        virtual void update() = 0;

    private:
    };

    inline JulianDay::~JulianDay() { };
}

#endif // CHORIZO_JULIANDAY_H_
