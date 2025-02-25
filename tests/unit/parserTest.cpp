#include <gtest/gtest.h>
#include "../../src/main.h"

extern "C" 
{
    void parser(char buffer[65536], size_t len);
}

void reset()
{
    val = 0;
    sym = 0;
    prev_symbol = -1;
    values[SIZE] = {0};
    symbols[SIZE] = {0};
}

char str[4*SIZE + 1];
TEST(ParserTests, goodTests)
{
    reset();
    strcpy(str, "11+4-5\n");
    EXPECT_NO_FATAL_FAILURE(parser(str, strlen(str)));
    EXPECT_EQ(values[0],11);
    EXPECT_EQ(values[1],4);
    EXPECT_EQ(values[2],5);
    EXPECT_EQ(symbols[0],'+');
    EXPECT_EQ(symbols[1],'-');

    reset();
    strcpy(str, "11/4*5\n");
    EXPECT_NO_FATAL_FAILURE(parser(str, strlen(str)));
    EXPECT_EQ(values[0],11);
    EXPECT_EQ(values[1],4);
    EXPECT_EQ(values[2],5);
    EXPECT_EQ(symbols[0],'/');
    EXPECT_EQ(symbols[1],'*');

    reset();
    strcpy(str, "11+(4*5)\n");
    EXPECT_NO_FATAL_FAILURE(parser(str, strlen(str)));
    EXPECT_EQ(values[0],11);
    EXPECT_EQ(values[1],4);
    EXPECT_EQ(values[2],5);
    EXPECT_EQ(symbols[0],'+');
    EXPECT_EQ(symbols[1],'(');
    EXPECT_EQ(symbols[2],'*');
    EXPECT_EQ(symbols[3],')');

    reset();
    strcpy(str, "11+(4)*5\n");
    EXPECT_NO_FATAL_FAILURE(parser(str, strlen(str)));
    EXPECT_EQ(values[0],11);
    EXPECT_EQ(values[1],4);
    EXPECT_EQ(values[2],5);
    EXPECT_EQ(symbols[0],'+');
    EXPECT_EQ(symbols[1],'(');
    EXPECT_EQ(symbols[2],')');
    EXPECT_EQ(symbols[3],'*');
}


TEST(ParserTests, badTests)
{
    reset();

    strcpy(str, "-11+4-5\n");
    EXPECT_EXIT(parser(str, strlen(str)), testing::ExitedWithCode(6), "");

    strcpy(str, "11-(-4*5)\n");
    EXPECT_EXIT(parser(str, strlen(str)), testing::ExitedWithCode(7), "");

    strcpy(str, "11--4*5\n");
    EXPECT_EXIT(parser(str, strlen(str)), testing::ExitedWithCode(7), "");

    strcpy(str, "+11-4*5\n");
    EXPECT_EXIT(parser(str, strlen(str)), testing::ExitedWithCode(8), "");

    strcpy(str, "11.3-4*5\n");
    EXPECT_EXIT(parser(str, strlen(str)), testing::ExitedWithCode(2), "");

    strcpy(str, "11%4*5\n");
    EXPECT_EXIT(parser(str, strlen(str)), testing::ExitedWithCode(2), "");

    strcpy(str, "");
    for (int i = 0; i < SIZE; i++)
    {
        strcat(str, "(9)+");
    }
    strcat(str, "\n");
    EXPECT_EXIT(parser(str, strlen(str)), testing::ExitedWithCode(3), "");
}