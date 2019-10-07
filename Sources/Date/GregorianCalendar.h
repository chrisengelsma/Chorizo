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
        static const std::string MonthName(int month);
        static const std::string WeekDayName(int weekDayNumber);

        GregorianCalendar();
        GregorianCalendar(const GregorianCalendar& cal);
        GregorianCalendar(const int& year, const int& month, const int& day);
        explicit GregorianCalendar(tm* time);
        explicit GregorianCalendar(const Almanac& almanac);

        int getYear()  const { return m_year; }
        int getMonth() const { return m_year; }
        int getDay()   const { return m_year; }

        std::string getMonthName() const;
        std::string getWeekDay() const override;

        std::string getDateString() const override;
        std::string getName() const override;


    };
}

#endif
