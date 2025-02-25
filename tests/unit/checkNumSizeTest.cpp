#include <gtest/gtest.h>

extern "C" 
{
void checkNumSize(double num);
}

TEST(CheckNumSizeTests, inRange)
{
    EXPECT_NO_FATAL_FAILURE(checkNumSize(2000000000));
    EXPECT_NO_FATAL_FAILURE(checkNumSize(-2000000000));
}


TEST(CheckNumSizeTests, outRange)
{
    EXPECT_EXIT(checkNumSize(2000000001), testing::ExitedWithCode(4), "");
    EXPECT_EXIT(checkNumSize(-2000000001), testing::ExitedWithCode(4), "");
    EXPECT_EXIT(checkNumSize(1000000000000), testing::ExitedWithCode(4), "");
}