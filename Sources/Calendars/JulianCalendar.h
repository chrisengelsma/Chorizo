#ifndef CHORIZO_JULIANCALENDAR_H_
#define CHORIZO_JULIANCALENDAR_H_

#ifndef CHORIZO_CALENDAR_H_
#include <Calendars/Calendar.h>
#endif

#ifndef CHORIZO_CONSTANTS_H_
#include <Utils/Constants.h>
#endif

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif

namespace chorizo
{
    class CHORIZO_EXPORT JulianCalendar : public virtual Calendar
    {
    protected:
        int m_year{};
        int m_month{};
        int m_day{};

    public:
        static constexpr double Epoch{2299160.5};

        /**
         * @brief Determines if a given year is a leap year.
         *
         * A year is considered to be a leap year in the Julian calendar if it is
         * divisible by four.
         *
         * @param year  a year.
         * @return      true, if year is a leap year; false, otherwise.
         */
        static const bool IsLeapYear(const int& year);

        /**
         * @brief Gets the number of days for a given month within a given year.
         *
         * @param year   a year.
         * @param month  a month.
         * @return       the number of days in the month.
         */
        static const uint32_t DaysInMonth(const int& year, const int& month);

        /**
         * @brief Returns an array of month lengths for a given year.
         *
         * @param year  a year.
         * @return      an array[12] of month lengths.
         */
        static const std::vector<uint32_t> MonthLengths(const int& year);

        /**
         * @brief Gets the name of a given month.
         * @param month  a month number in the range [1, 12].
         * @return       the name of the month.
         */
        static const std::string MonthName(int month);

        /**
         * @brief Gets the week day name for a week day number.
         * @param weekDayNumber  a week day number [0, 6].
         * @return               the name of the weekday.
         */
        static const std::string WeekDayName(int weekDayNumber);

        JulianCalendar();
        JulianCalendar(const JulianCalendar& cal);
        JulianCalendar(const int& year, const int& month, const int& day);
        explicit JulianCalendar(const double& jday);
        explicit JulianCalendar(Calendar* cal);

        virtual ~JulianCalendar() { }

        virtual bool isLeapYear() const;

        void setYear(const int& year);
        void setMonth(const int& month);
        void setDay(const int& day);
        void setYearMonthDay(const int& year, const int& month, const int& day);

        int getYear() const { return m_year; }
        int getMonth() const { return m_month; }
        int getDay() const { return m_day; }

        // virtual
        virtual std::string getName() const override { return "Julian Calendar"; }
        virtual std::string getDateString() const override;
        virtual std::string getWeekDayName() const override;
        virtual std::string getMonthName() const override;
        virtual uint32_t getDaysPerWeek() const override { return 7; }
        virtual uint32_t getMonthsPerYear() const override { return 12; }
        virtual uint32_t getDaysInMonth() const override;

    protected:
        virtual void updateInternal() override;
    };
}

#endif // CHORIZO_JULIANCALENDAR_H_
