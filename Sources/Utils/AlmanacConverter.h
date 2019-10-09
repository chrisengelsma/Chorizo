#ifndef CHORIZO_ALMANACCONVERTER_H_
#define CHORIZO_ALMANACCONVERTER_H_

#include "StdAfx.h"

namespace chorizo
{
    class JulianDay;
    class GregorianCalendar;
}

namespace chorizo
{
    class AlmanacConverter
    {
    public:
        static double ToJulianDay(JulianDay* julianDay);
        static GregorianCalendar* ToGregorianCalendar(JulianDay* julianDay);

    private:
        static double g2jd(GregorianCalendar* gc);
        static GregorianCalendar* jd2g(const double& jd);
    };
}

#endif
