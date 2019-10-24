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

#ifndef CHORIZO_JULIANCALENDAR_H_
#include <Calendars/JulianCalendar.h>
#endif

#ifndef CHORIZO_CONSTANTS_H_
#include <Utils/Constants.h>
#endif

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif


namespace chorizo
{

    class CHORIZO_EXPORT GregorianCalendar : public virtual JulianCalendar
    {
    public:
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

        static const uint32_t DaysInMonth(const int& year, const int& month);

        static const std::vector<uint32_t> MonthLengths(const int& year);

        GregorianCalendar();
        GregorianCalendar(const GregorianCalendar& cal);
        GregorianCalendar(const int& year, const int& month, const int& day);
        explicit GregorianCalendar(const double& jday);
        explicit GregorianCalendar(Calendar* cal);

        virtual ~GregorianCalendar() { };

        virtual uint32_t getDaysInMonth() const override;

        bool isLeapYear() const override;

        // virtual
        virtual std::string getName() const override { return "Gregorian Calendar"; }
    protected:
        virtual void updateInternal() override;
    };
}

#endif // CHORIZO_GREGORIANCALENDAR_H_
