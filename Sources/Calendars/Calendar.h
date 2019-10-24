#ifndef CHORIZO_CALENDAR_H_
#define CHORIZO_CALENDAR_H_

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif

namespace chorizo
{
    class CHORIZO_EXPORT Calendar
    {
    private:
        static constexpr double Epoch{2400000.5};

    public:

        Calendar();
        Calendar(const Calendar& a);
        Calendar(const double& jday);

        virtual ~Calendar() = 0;

        virtual std::string getName() const = 0;
        virtual std::string getDateString() const = 0;
        virtual std::string getWeekDayName() const = 0;
        virtual std::string getMonthName() const = 0;
        virtual uint32_t getDaysPerWeek() const = 0;
        virtual uint32_t getMonthsPerYear() const = 0;
        virtual uint32_t getDaysInMonth() const = 0;
        virtual const double getEpoch() const { return Calendar::Epoch; }

        double getJulianDay(const bool& modified = false, const double& epoch = 0) const;
        uint32_t getWeekDayNumber() const;

        virtual std::string toString() const;
        friend std::ostream& operator<<(std::ostream& stream, const Calendar& a);

        friend bool operator>(const Calendar& lhs, const Calendar& rhs);
        friend bool operator>=(const Calendar& lhs, const Calendar& rhs);
        friend bool operator<(const Calendar& lhs, const Calendar& rhs);
        friend bool operator<=(const Calendar& lhs, const Calendar& rhs);
        friend bool operator==(const Calendar& lhs, const Calendar& rhs);
        friend bool operator!=(const Calendar& lhs, const Calendar& rhs);

    protected:
        double m_jday{};

        virtual void updateInternal() = 0;

    };

    inline Calendar::~Calendar() { }
}

#endif //CHORIZO_CALENDAR_H_
