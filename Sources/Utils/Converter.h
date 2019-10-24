#ifndef CHORIZO_CONVERTER_H_
#define CHORIZO_CONVERTER_H_

#ifndef CHORIZO_CALENDAR_H_
#include <Calendars/Calendar.h>
#endif

#ifndef CHORIZO_JULIANCALENDAR_H_
#include <Calendars/JulianCalendar.h>
#endif

#ifndef CHORIZO_GREGORIANCALENDAR_H_
#include <Calendars/GregorianCalendar.h>
#endif

namespace chorizo
{
    class CHORIZO_EXPORT Converter
    {
    public:
        static const double ToJulianDay(const Calendar* cal);
        static const GregorianCalendar* ToGregorianCalendar(const Calendar* cal);
        static const GregorianCalendar* ToGregorianCalendar(const double& jday);

        static const JulianCalendar* ToJulianCalendar(const Calendar* cal);
        static const JulianCalendar* ToJulianCalendar(const double& jday);

    private:
        static const GregorianCalendar* jd2g(const double& jday);
        static const JulianCalendar* jd2j(const double& jday);

        static const double g2jd(const GregorianCalendar* cal);
        static const double j2jd(const JulianCalendar* cal);
    };
}

#endif // CHORIZO_CONVERTER_H_
