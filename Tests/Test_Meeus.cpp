#include <gtest/gtest.h>

#include <Astro/Meeus.h>
#include <iostream>

using namespace chorizo;

TEST(Meeus, Equinox_AutumnalEquinox)
{
    // Autumnal Equinox 2015 = 9/23 @ 08:21:33.9 UTC
    double expected = 2457288.848309;
    double result   = Meeus::Equinox(2015, Season::Autumn);
    EXPECT_FLOAT_EQ(expected, result);
}

TEST(Meeus, Equinox_SpringEquinox)
{
    // Spring Equinox 2015 = 3/20 @ 22:46:20.6 UTC
    double expected = 2457102.448850;
    double result   = Meeus::Equinox(2015, Season::Spring);
    EXPECT_FLOAT_EQ(expected, result);
}

TEST(Meeus, Equinox_SummerSolstice)
{
    // Summer Solstice 2015 = 6/21 @ 16:39:00.5 UTC
    double expected = 2457195.193756;
    double result   = Meeus::Equinox(2015, Season::Summer);
    EXPECT_FLOAT_EQ(expected, result);
}

TEST(Meeus, Equinox_WinterSolstice)
{
    // Winter Solstice 2015 = 12/22 @ 04:49:20.3 UTC
    double expected = 2457378.700929;
    double result   = Meeus::Equinox(2015, Season::Winter);
    EXPECT_FLOAT_EQ(expected, result);
}

TEST(Meeus, DeltaT)
{
    EXPECT_FLOAT_EQ(1863.875977, Meeus::DeltaT(940));
    EXPECT_FLOAT_EQ(7.0, Meeus::DeltaT(1701));
    EXPECT_FLOAT_EQ(65.0, Meeus::DeltaT(2000));
    EXPECT_FLOAT_EQ(1244.5, Meeus::DeltaT(2500));
}

TEST(Meeus, LunarPhase)
{
    EXPECT_FLOAT_EQ(306.55707, Meeus::LunarPhase(0));
    EXPECT_FLOAT_EQ(161.57429, Meeus::LunarPhase(100));
    EXPECT_FLOAT_EQ(343.88849, Meeus::LunarPhase(1000));
    EXPECT_FLOAT_EQ(79.37363, Meeus::LunarPhase(10000));
    EXPECT_FLOAT_EQ(184.06479, Meeus::LunarPhase(100000));
}

TEST(Meeus, LunarIllumination)
{
    EXPECT_FLOAT_EQ(100.0, Meeus::LunarIlluminationFromPhase(0));
    EXPECT_FLOAT_EQ(50.0,  Meeus::LunarIlluminationFromPhase(90));
    EXPECT_FLOAT_EQ(0.0,   Meeus::LunarIlluminationFromPhase(180));
    EXPECT_FLOAT_EQ(50.0,  Meeus::LunarIlluminationFromPhase(270));
    EXPECT_FLOAT_EQ(100.0f,Meeus::LunarIlluminationFromPhase(360));
}
