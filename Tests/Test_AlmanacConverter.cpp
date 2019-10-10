#include <gtest/gtest.h>

#include <Utils/Converter.h>
#include <Date/GregorianCalendar.h>

#include <iostream>

using namespace chorizo;

TEST(AlmanacConverter, ToJulianDay_FromGregorianCalendar)
{
    auto cal = new GregorianCalendar(1987, 3, 10);
    double jday = Converter::ToJulianDay(cal);
    delete cal; cal = nullptr;
    EXPECT_EQ(jday, 2446864.5);
}

