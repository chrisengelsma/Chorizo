#include <gtest/gtest.h>

#ifndef CHORIZO_CALENDAR_H_
#include <Calendars/Calendar.h>
#endif

#ifndef CHORIZO_JULIANCALENDAR_H_
#include <Calendars/JulianCalendar.h>
#endif

#ifndef CHORIZO_CONSTANTS_H_
#include <Utils/Constants.h>
#endif

#include <iostream>

using namespace chorizo;

TEST(JulianCalendar, Constructor_FromDate)
{
    auto cal = JulianCalendar(1987, 3, 10);
    EXPECT_EQ(cal.getYear(), 1987);
    EXPECT_EQ(cal.getMonth(), 3);
    EXPECT_EQ(cal.getDay(), 10);
    EXPECT_EQ(cal.getJulianDay(), 2446877.5);
}

TEST(JulianCalendar, Constructor_Copy)
{
    auto cal0 = JulianCalendar(1987, 3, 10);
    auto cal1 = JulianCalendar(cal0);

    EXPECT_EQ(cal0.getYear(), 1987);
    EXPECT_EQ(cal0.getMonth(), 3);
    EXPECT_EQ(cal0.getDay(), 10);
    EXPECT_EQ(cal0.getJulianDay(), 2446877.5);
}

TEST(JulianCalendar, Constructor_FromPointer)
{
    auto cal0 = new JulianCalendar(1987, 3, 10);
    auto cal1 = JulianCalendar(cal0);
    EXPECT_EQ(cal1.getYear(), 1987);
    EXPECT_EQ(cal1.getMonth(), 3);
    EXPECT_EQ(cal1.getDay(), 10);
    EXPECT_EQ(cal1.getJulianDay(), 2446877.5);
}

TEST(JulianCalendar, GetName)
{
    JulianCalendar cal;
    EXPECT_EQ(cal.getName(), "Julian Calendar");
}

TEST(JulianCalendar, GetWeekdayName)
{
    auto cal = JulianCalendar(1987, 3, 9);

    // Sunday -> Saturday
    auto weekdays = Constants().get(Constants::WeekDayNames, Constants::JulianCalendar);

    for (auto i = 0; i<7; ++i)
    {
        EXPECT_EQ(cal.getWeekDayName(), weekdays[i]);
        cal.setDay(cal.getDay() + 1);
    }
}

TEST(JulianCalendar, SetDay)
{
    auto cal0 = JulianCalendar(1987, 3, 10);
    cal0.setDay(11);

    EXPECT_EQ(cal0.getYear(), 1987);
    EXPECT_EQ(cal0.getMonth(), 3);
    EXPECT_EQ(cal0.getDay(), 11);
    EXPECT_EQ(cal0.getJulianDay(), 2446878.5);
}

TEST(JulianCalendar, SetMonth)
{
    auto cal0 = JulianCalendar(1987, 3, 10);
    cal0.setMonth(9);

    EXPECT_EQ(cal0.getYear(), 1987);
    EXPECT_EQ(cal0.getMonth(), 9);
    EXPECT_EQ(cal0.getDay(), 10);
    EXPECT_EQ(cal0.getJulianDay(), 2447061.5);
}

TEST(JulianCalendar, SetYear)
{
    auto cal0 = JulianCalendar(1987, 3, 10);
    cal0.setYear(1986);

    EXPECT_EQ(cal0.getYear(), 1986);
    EXPECT_EQ(cal0.getMonth(), 3);
    EXPECT_EQ(cal0.getDay(), 10);
    EXPECT_EQ(cal0.getJulianDay(), 2446512.5);
}

TEST(JulianCalendar, GetDaysPerWeek)
{
    EXPECT_EQ(JulianCalendar().getDaysPerWeek(), 7);
}

TEST(JulianCalendar, GetMonthsPerYear)
{
    EXPECT_EQ(JulianCalendar().getMonthsPerYear(), 12);
}

TEST(JulianCalendar, DaysInMonth)
{
    uint32_t monthsLeap[12]    = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint32_t monthsRegular[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    auto months2000 = JulianCalendar::MonthLengths(2000);
    auto months2001 = JulianCalendar::MonthLengths(2001);
    auto months1900 = JulianCalendar::MonthLengths(1900);

    auto cal2000 = JulianCalendar(2000, 1, 1);
    auto cal2001 = JulianCalendar(2001, 1, 1);
    auto cal1900 = JulianCalendar(1900, 1, 1);

    for (uint32_t i = 0; i<12; ++i)
    {
        cal2000.setMonth(i + 1);
        cal2001.setMonth(i + 1);
        cal1900.setMonth(i + 1);

        EXPECT_EQ(cal2000.getDaysInMonth(), monthsLeap[i]);
        EXPECT_EQ(cal2001.getDaysInMonth(), monthsRegular[i]);
        EXPECT_EQ(cal1900.getDaysInMonth(), monthsLeap[i]);

        EXPECT_EQ(JulianCalendar::DaysInMonth(2000, i + 1), monthsLeap[i]);
        EXPECT_EQ(JulianCalendar::DaysInMonth(2001, i + 1), monthsRegular[i]);
        EXPECT_EQ(JulianCalendar::DaysInMonth(1900, i + 1), monthsLeap[i]);

        EXPECT_EQ(months2000[i], monthsLeap[i]);
        EXPECT_EQ(months2001[i], monthsRegular[i]);
        EXPECT_EQ(months1900[i], monthsLeap[i]);
    }

}

TEST(JulianCalendar, Comparators)
{
    auto cal0 = JulianCalendar(1987, 3, 10);
    auto cal1 = JulianCalendar(1987, 3, 10);
    auto cal2 = JulianCalendar(1986, 9, 3);

    EXPECT_TRUE(cal0 == cal1);
    EXPECT_TRUE(cal0 != cal2);
    EXPECT_TRUE(cal1 != cal2);

    EXPECT_TRUE(cal2<cal0);
    EXPECT_TRUE(cal0<=cal1);
    EXPECT_TRUE(cal0>cal2);
    EXPECT_TRUE(cal0>=cal1);
}
