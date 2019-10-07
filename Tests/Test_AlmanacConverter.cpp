#include <gtest/gtest.h>

#include <Utils/AlmanacConverter.h>
#include <Date/GregorianCalendar.h>

#include <iostream>

using namespace chorizo;

TEST(AlmanacConverter, ToJulianDay_FromGregorianCalendar)
{
    GregorianCalendar cal(1987, 3, 10);
    double jday = AlmanacConverter::ToJulianDay(cal);
    EXPECT_EQ(jday, 2446864.5);
}

