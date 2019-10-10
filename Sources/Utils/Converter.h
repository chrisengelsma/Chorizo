#ifndef CHORIZO_CONVERTER_H_
#define CHORIZO_CONVERTER_H_

#include "StdAfx.h"

namespace chorizo
{
    class JulianDay;
    class GregorianCalendar;
}

namespace chorizo
{
    template<typename T>
    class Converter
    {
    public:
        static GregorianCalendar* ToGregorianCalendar(T* cal);

    private:
        static double g2jd(GregorianCalendar* gc);
        static GregorianCalendar* jd2g(const double& jd);
    };
}

#include "Converter.inl"

#endif
