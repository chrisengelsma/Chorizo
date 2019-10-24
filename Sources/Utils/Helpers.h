#ifndef CHORIZO_HELPERS_H_
#define CHORIZO_HELPERS_H_

#ifndef CHORIZO_CALENDAR_H_
#include <Calendars/Calendar.h>
#endif

#ifndef CHORIZO_STDAFX_H_
#include <StdAfx.h>
#endif

namespace chorizo
{
    class CHORIZO_EXPORT Helpers
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

#endif //CHORIZO_HELPERS_H_
