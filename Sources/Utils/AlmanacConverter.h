#ifndef CHORIZO_ALMANACCONVERTER_H_
#define CHORIZO_ALMANACCONVERTER_H_

#include "StdAfx.h"

namespace chorizo
{
    class Almanac;
    class JulianDay;
    class GregorianCalendar;
}

namespace chorizo
{
    class AlmanacConverter
    {
    public:
        static double ToJulianDay(const Almanac& almanac);
        static GregorianCalendar ToGregorianCalendar(const Almanac& almanac);

    private:
        static double g2jd(const GregorianCalendar& gc);
        static GregorianCalendar jd2g(const double& jd);
    };
}

#endif
