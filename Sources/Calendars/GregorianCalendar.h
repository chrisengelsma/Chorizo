/**
 * @class chorizo::GregorianCalendar
 * @brief A Gregorian calendar.
 *
 * The Gregorian Calendar is internationally the most widely used civil
 * calendar. It was named for Pope Gregory XIII who introduced it on
 * October 15, 1582. The calendar was a refinement to the Julian Calendar,
 * with the motivation of setting the Easter holiday to a specific date
 * instead of the spring equinox, which naturally drifted dates.
 *
 * Each year is divided into 12 months, with a varied number of days per
 * month. To account for the drift in seasons, a leap year occurs which
 * introduces an additional day in February. These leap years happen every
 * year that's divisible by 4, except years that are divisible by 100 but
 * not divisible by 400. For example: 1700, 1800 and 1900 are NOT leap
 * years, but 2000 is a leap year.
 *
 * @author Chris Engelsma <chris.engelsma@gmail.com>
 * @version 2019.10.18
 */

#ifndef CHORIZO_GREGORIANCALENDAR_H_
#define CHORIZO_GREGORIANCALENDAR_H_

#ifndef CHORIZO_CALENDAR_H_
#include <Date/Calendar.h>

#endif

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif

namespace chorizo
{

    class CHORIZO_EXPORT GregorianCalendar : public virtual Calendar
    {
    private:
        int m_year{};
        int m_month{};
        int m_day{};

    public:
        static constexpr double Epoch = 2299160.5;

        /**
         * @brief Determines if a given year is a leap year.
         *
         * This method optionally determines whether the current date exists
         * before or after the creation of the Gregorian calendar, and follows
         * that calendar's leap year rule. As a result, there are "missing dates"
         * (October 4 - 14, 1582).
         *
         * @param year       a year.
         * @param proleptic  true, if using a proleptic calendar; false, otherwise.
         * @return           true, if year is a leap year; false, otherwise.
         */
        static const bool IsLeapYear(const int& year, const bool& proleptic = true);

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

        GregorianCalendar();
        GregorianCalendar(const GregorianCalendar& cal);
        GregorianCalendar(const int& year, const int& month, const int& day);
        explicit GregorianCalendar(const double& jday);
        explicit GregorianCalendar(Calendar* almanac);

        bool isLeapYear() const;

        int getYear() const
        { return m_year; }
        int getMonth() const
        { return m_month; }
        int getDay() const
        { return m_day; }


        void setDay(const int& day);
        void setMonth(const int& month);
        void setYear(const int& year);


        // virtual
        std::string getName() const override
        { return "Gregorian Calendar"; }
        std::string getDateString() const override;
        std::string getWeekDayName() const override;
        std::string getMonthName() const override;
        uint32_t getDaysPerWeek() const override
        { return 7; }
        uint32_t getMonthsPerYear() const override
        { return 12; }
        uint32_t getDaysInMonth() const override;

    protected:
        void updateInternal() override;
    };
}

#endif // CHORIZO_GREGORIANCALENDAR_H_
