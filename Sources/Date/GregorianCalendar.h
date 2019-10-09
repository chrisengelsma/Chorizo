#ifndef CHORIZO_GREGORIANCALENDAR_H_
#define CHORIZO_GREGORIANCALENDAR_H_

#include "StdAfx.h"
#include "Almanac.h"

namespace chorizo
{
    class CHORIZO_EXPORT GregorianCalendar : public Almanac
    {
    private:
        int m_year{};
        int m_month{};
        int m_day{};

    public:
        static std::string MonthName(int month);
        static std::string WeekDayName(int weekDayNumber);

        GregorianCalendar();
        GregorianCalendar(const int& year, const int& month, const int& day);

        explicit GregorianCalendar(tm* time);
        explicit GregorianCalendar(Almanac* almanac);

        [[nodiscard]] int getYear()  const { return m_year; }
        [[nodiscard]] int getMonth() const { return m_month; }
        [[nodiscard]] int getDay()   const { return m_day; }

        [[nodiscard]] std::string getMonthName() const;

        // Almanac
        [[nodiscard]] std::string getDateString() const override;
        [[nodiscard]] std::string getWeekDay() const override;

    protected:
        const std::string m_name{"Gregorian Calendar"};
        const size_t m_daysPerWeek{7};
        const size_t m_monthsPerYear{12};

    };
}

#endif
