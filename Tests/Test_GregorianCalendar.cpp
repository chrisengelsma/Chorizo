#include <gtest/gtest.h>

#ifndef CHORIZO_CALENDAR_H_
#include <Calendars/Calendar.h>
#endif

#ifndef CHORIZO_GREGORIANCALENDAR_H_
#include <Calendars/GregorianCalendar.h>
#endif

#ifndef CHORIZO_CONSTANTS_H_
#include <Utils/Constants.h>
#endif

using namespace chorizo;

TEST(GregorianCalendar, Constructor_FromDate)
{
    auto cal = GregorianCalendar(1987, 3, 10);
    EXPECT_EQ(cal.getYear(), 1987);
    EXPECT_EQ(cal.getMonth(), 3);
    EXPECT_EQ(cal.getDay(), 10);
    EXPECT_EQ(cal.getJulianDay(), 2446864.5);
}

TEST(GregorianCalendar, Constructor_Copy)
{
    auto cal0 = GregorianCalendar(1987, 3, 10);
    auto cal1 = GregorianCalendar(cal0);

    EXPECT_EQ(cal0.getYear(), 1987);
    EXPECT_EQ(cal0.getMonth(), 3);
    EXPECT_EQ(cal0.getDay(), 10);
    EXPECT_EQ(cal0.getJulianDay(), 2446864.5);
}

TEST(GregorianCalendar, GetName)
{
    GregorianCalendar cal;
    EXPECT_EQ(cal.getName(), "Gregorian Calendar");
}

TEST(GregorianCalendar, GetWeekdayName)
{
    auto cal = GregorianCalendar(1987, 3, 8);

    // Sunday -> Saturday
    auto weekdays = Constants().get(Constants::WeekDayNames, Constants::JulianCalendar);

    for (auto i = 0; i<7; ++i)
    {
        EXPECT_EQ(cal.getWeekDayName(), weekdays[i]);
        cal.setDay(cal.getDay() + 1);
    }
}

TEST(GregorianCalendar, SetDay)
{
    auto cal0 = GregorianCalendar(1987, 3, 10);
    cal0.setDay(11);

    EXPECT_EQ(cal0.getYear(), 1987);
    EXPECT_EQ(cal0.getMonth(), 3);
    EXPECT_EQ(cal0.getDay(), 11);
    EXPECT_EQ(cal0.getJulianDay(), 2446865.5);
}

TEST(GregorianCalendar, SetMonth)
{
    auto cal0 = GregorianCalendar(1987, 3, 10);
    cal0.setMonth(9);

    EXPECT_EQ(cal0.getYear(), 1987);
    EXPECT_EQ(cal0.getMonth(), 9);
    EXPECT_EQ(cal0.getDay(), 10);
    EXPECT_EQ(cal0.getJulianDay(), 2447048.5);
}

TEST(GregorianCalendar, SetYear)
{
    auto cal0 = GregorianCalendar(1987, 3, 10);
    cal0.setYear(1986);

    EXPECT_EQ(cal0.getYear(), 1986);
    EXPECT_EQ(cal0.getMonth(), 3);
    EXPECT_EQ(cal0.getDay(), 10);
    EXPECT_EQ(cal0.getJulianDay(), 2446499.5);
}

TEST(GregorianCalendar, GetDaysPerWeek)
{
    EXPECT_EQ(GregorianCalendar().getDaysPerWeek(), 7);
}

TEST(GregorianCalendar, GetMonthsPerYear)
{
    EXPECT_EQ(GregorianCalendar().getMonthsPerYear(), 12);
}

TEST(GregorianCalendar, DaysInMonth)
{
    uint32_t monthsLeap[12]    = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint32_t monthsRegular[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    auto months2000 = GregorianCalendar::MonthLengths(2000);
    auto months2001 = GregorianCalendar::MonthLengths(2001);
    auto months1900 = GregorianCalendar::MonthLengths(1900);

    auto cal2000 = GregorianCalendar(2000, 1, 1);
    auto cal2001 = GregorianCalendar(2001, 1, 1);
    auto cal1900 = GregorianCalendar(1900, 1, 1);

    for (uint32_t i = 0; i<12; ++i)
    {
        cal2000.setMonth(i + 1);
        cal2001.setMonth(i + 1);
        cal1900.setMonth(i + 1);

        EXPECT_EQ(cal2000.getDaysInMonth(), monthsLeap[i]);
        EXPECT_EQ(cal2001.getDaysInMonth(), monthsRegular[i]);
        EXPECT_EQ(cal1900.getDaysInMonth(), monthsRegular[i]);

        EXPECT_EQ(GregorianCalendar::DaysInMonth(2000, i + 1), monthsLeap[i]);
        EXPECT_EQ(GregorianCalendar::DaysInMonth(2001, i + 1), monthsRegular[i]);
        EXPECT_EQ(GregorianCalendar::DaysInMonth(1900, i + 1), monthsRegular[i]);

        EXPECT_EQ(months2000[i], monthsLeap[i]);
        EXPECT_EQ(months2001[i], monthsRegular[i]);
        EXPECT_EQ(months1900[i], monthsRegular[i]);
    }

}

TEST(GregorianCalendar, Comparators)
{
    auto cal0 = GregorianCalendar(1987, 3, 10);
    auto cal1 = GregorianCalendar(1987, 3, 10);
    auto cal2 = GregorianCalendar(1986, 9, 3);

    EXPECT_TRUE(cal0 == cal1);
    EXPECT_TRUE(cal0 != cal2);
    EXPECT_TRUE(cal1 != cal2);

    EXPECT_TRUE(cal2<cal0);
    EXPECT_TRUE(cal0<=cal1);
    EXPECT_TRUE(cal0>cal2);
    EXPECT_TRUE(cal0>=cal1);
}
