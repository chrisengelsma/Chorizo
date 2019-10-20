#ifndef CHORIZO_BASECALENDAR_H_
#define CHORIZO_BASECALENDAR_H_

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif

namespace chorizo
{
    class GregorianCalendar;

    class CHORIZO_EXPORT BaseCalendar
    {

    public:
        static constexpr double Epoch = 2400000.5;

        virtual ~BaseCalendar() = 0;

        virtual std::string getName() const = 0;
        virtual std::string getDateString() const = 0;
        virtual std::string getWeekDayName() const = 0;
        virtual std::string getMonthName() const = 0;
        virtual uint32_t getDaysPerWeek() const = 0;
        virtual uint32_t getMonthsPerYear() const = 0;
        virtual uint32_t getDaysInMonth() const = 0;

        double getJulianDay(const bool& modified = false) const;
        uint32_t getWeekDayNumber() const;

        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& stream, const BaseCalendar& a);

        friend bool operator>(const BaseCalendar& lhs, const BaseCalendar& rhs);
        friend bool operator>=(const BaseCalendar& lhs, const BaseCalendar& rhs);
        friend bool operator<(const BaseCalendar& lhs, const BaseCalendar& rhs);
        friend bool operator<=(const BaseCalendar& lhs, const BaseCalendar& rhs);
        friend bool operator==(const BaseCalendar& lhs, const BaseCalendar& rhs);
        friend bool operator!=(const BaseCalendar& lhs, const BaseCalendar& rhs);

    protected:
        double m_jday{};

        virtual void updateInternal() = 0;

    };

    inline BaseCalendar::~BaseCalendar() { }
}

#endif //CHORIZO_BASECALENDAR_H_
