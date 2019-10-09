#ifndef CHORIZO_ALMANACCONVERTER_H_
#define CHORIZO_ALMANACCONVERTER_H_

#include "StdAfx.h"

namespace chorizo
{
    class Almanac;
    class GregorianCalendar;
}

namespace chorizo
{
    class AlmanacConverter
    {
    public:
        static double ToJulianDay(Almanac* almanac);
        static GregorianCalendar* ToGregorianCalendar(Almanac* almanac);

    private:
        static double g2jd(GregorianCalendar* gc);
        static GregorianCalendar* jd2g(const double& jd);
    };
}

#endif
