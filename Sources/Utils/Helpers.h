#ifndef CHORIZO_CALENDARUTILS_H_
#define CHORIZO_CALENDARUTILS_H_

#include <Date/Calendar.h>
#include <StdAfx.h>

namespace chorizo
{
    class CalendarUtils
    {
    public:
        static const bool DatesAreReverseChronological(std::vector<Calendar*>& dates)
        {
            if (dates.size() == 0)
            {
                return false;
            }

            auto jday0 = dates[0]->getJulianDay();

            for (auto cal : dates)
            {
                auto jday1 = cal->getJulianDay();
                if (jday1>jday0) return false;
                jday0 = jday1;
            }
            return true;
        }
    };
}

#endif // CHORIZO_CALENDARUTILS_H_
