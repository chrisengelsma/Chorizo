#ifndef CHORIZO_GREGORIANCALENDAR_H_
#define CHORIZO_GREGORIANCALENDAR_H_

#include "StdAfx.h"
#include "JulianDay.h"

namespace chorizo
{
    class CHORIZO_EXPORT GregorianCalendar : public JulianDay
    {
    private:
        int m_year{};
        int m_month{};
        int m_day{};

    public:
        static std::string MonthName(int month);

        static std::string WeekDayName(int weekDayNumber);

        GregorianCalendar();

        GregorianCalendar(const GregorianCalendar& cal);

        GregorianCalendar(const int& year, const int& month, const int& day);

        explicit GregorianCalendar(tm* time);

        explicit GregorianCalendar(JulianDay* almanac);

        bool isLeapYear() const;

        int getYear()  const { return m_year; }

        int getMonth() const { return m_month; }

        int getDay()   const { return m_day; }

        void setDay(const int& day);

        void setMonth(const int& month);

        void setYear(const int& year);

        std::string getMonthName() const;

        // JulianDay
        std::string getDateString() const override;
        std::string getWeekDay() const override;

    protected:
        void update() override;

        const std::string m_name{"Gregorian Calendar"};
        const uint32_t m_daysPerWeek{7};
        const uint32_t m_monthsPerYear{12};
    };
}

#endif // CHORIZO_GREGORIANCALENDAR_H_
