#ifndef CHORIZO_CONSTANTS_H_
#define CHORIZO_CONSTANTS_H_

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>

#endif

namespace chorizo
{
    class CHORIZO_EXPORT Constants
    {
    public:
        enum CalendarKey
        {
            JulianCalendar
        };

        enum StringKey
        {
            WeekDayNames,
            MonthNames
        };

        const std::vector<std::string> get(const StringKey& stringKey, const CalendarKey& calendarKey)
        {
            return Lookup.at(stringKey).at(calendarKey);
        }

        const std::string get(const StringKey& stringKey, const CalendarKey& calendarKey, const int& index)
        {
            assert(index>=0);
            return get(stringKey, calendarKey)[index];
        }

    private:
        const std::vector<std::string> julianWeekDays = {
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday"
        };

        const std::vector<std::string> julianMonths = {
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
        };

        const std::map<CalendarKey, std::vector<std::string>> WeekDayMap = {
            {JulianCalendar, julianWeekDays},
        };

        const std::map<CalendarKey, std::vector<std::string>> MonthMap = {
            {JulianCalendar, julianMonths},
        };


        const std::map<StringKey, std::map<CalendarKey, std::vector<std::string>>> Lookup = {
            {WeekDayNames, WeekDayMap},
            {MonthNames,   MonthMap}
        };


    };
}

#endif //CHORIZO_CONSTANTS_H_
