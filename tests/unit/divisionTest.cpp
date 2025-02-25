#include "../../src/main.h"
#include <gtest/gtest.h>

extern "C"
{
    double division(double first, double second);
}

TEST(DivisionTests, smallNumbers)
{
    is_float = 0;
    EXPECT_EXIT(division(10, 0), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, 0.0001), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, -0.0001), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, 0.00000501), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, -0.0000081), testing::ExitedWithCode(1), "");
    is_float = 1;
    EXPECT_EXIT(division(10, 0), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, 0.0001), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, -0.0001), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, 0.00000401), testing::ExitedWithCode(1), "");
    EXPECT_EXIT(division(10, -0.00000071), testing::ExitedWithCode(1), "");
}

TEST(DivisionTests, goodNumbers)
{
    is_float = 0;
    EXPECT_EQ(division(13, 4), 3);
    EXPECT_EQ(division(-13, 4), -3);
    EXPECT_EQ(division(13, 0.01), 1300);
    EXPECT_EQ(division(5, 15), 0);
    is_float = 1;
    EXPECT_DOUBLE_EQ(division(13, 4), 3.25);
    EXPECT_DOUBLE_EQ(division(-13, 4), -3.25);
    EXPECT_DOUBLE_EQ(division(13, 0.01), 1300);
    EXPECT_DOUBLE_EQ(division(4, 16), 0.25);
}