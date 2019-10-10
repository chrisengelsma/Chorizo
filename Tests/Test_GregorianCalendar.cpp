#include <gtest/gtest.h>

#include <Date/GregorianCalendar.h>

#include <iostream>

using namespace chorizo;

TEST(GregorianCalendar, Constructor_FromDate)
{
    auto cal = new GregorianCalendar(1987, 3, 10);
    EXPECT_EQ(cal->getYear(), 1987);
    EXPECT_EQ(cal->getMonth(), 3);
    EXPECT_EQ(cal->getDay(), 10);
    EXPECT_EQ(cal->getJulianDay(), 2446864.5);
}

TEST(GregorianCalendar, Constructor_Copy)
{
    auto cal0 = new GregorianCalendar(1987, 3, 10);
    auto cal1= new GregorianCalendar(cal0);

    EXPECT_EQ(cal0->getYear(), 1987);
    EXPECT_EQ(cal0->getMonth(), 3);
    EXPECT_EQ(cal0->getDay(), 10);
    EXPECT_EQ(cal0->getJulianDay(), 2446864.5);
}

TEST(GregorianCalendar, SetDay)
{
    auto cal0 = new GregorianCalendar(1987, 3, 10);
    cal0->setDay(11);

    EXPECT_EQ(cal0->getYear(), 1987);
    EXPECT_EQ(cal0->getMonth(), 3);
    EXPECT_EQ(cal0->getDay(), 11);
    EXPECT_EQ(cal0->getJulianDay(), 2446865.5);
}

TEST(GregorianCalendar, SetMonth)
{
    auto cal0 = new GregorianCalendar(1987, 3, 10);
    cal0->setMonth(9);

    EXPECT_EQ(cal0->getYear(), 1987);
    EXPECT_EQ(cal0->getMonth(), 9);
    EXPECT_EQ(cal0->getDay(), 10);
    EXPECT_EQ(cal0->getJulianDay(), 2447048.5);
}

TEST(GregorianCalendar, SetYear)
{
    auto cal0 = new GregorianCalendar(1987, 3, 10);
    cal0->setYear(1986);

    EXPECT_EQ(cal0->getYear(), 1986);
    EXPECT_EQ(cal0->getMonth(), 3);
    EXPECT_EQ(cal0->getDay(), 10);
    EXPECT_EQ(cal0->getJulianDay(), 2446499.5);
}

TEST(GregorianCalendar, GetNumberOfDaysPerWeek)
{

}

TEST(GregorianCalendar, SetJulianDay)
{
    auto cal0 = new GregorianCalendar(1986, 9, 3);
    cal0->setJulianDay(2446864.5);

    EXPECT_EQ(cal0->getYear(), 1987);
    EXPECT_EQ(cal0->getMonth(), 3);
    EXPECT_EQ(cal0->getDay(), 10);
    EXPECT_EQ(cal0->getJulianDay(), 2446864.5);
}
