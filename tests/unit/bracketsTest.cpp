#include "../../src/main.h"
#include <gtest/gtest.h>

extern "C"
{
    double evaluate_brackets(double init);
}

void setGlobals(int values_[SIZE], char symbols_[SIZE], int val_, int sym_, int is_float_)
{
    val = val_;
    sym = sym_;
    for (int i = 0; i < val; i++)
        values[i] = values_[i];
    for (int i = 0; i < sym; i++)
        symbols[i] = symbols_[i];
    is_float = is_float_;
    current_sym = 0;
    current_val = 1;
}

TEST(bracketsTests, goodTests)
{
    int v1[] = {11, 3, 6};
    char s1[] = {'(', '+', ')', '*'};
    setGlobals(v1, s1, 3, 4, 0);
    EXPECT_EQ(evaluate_brackets(11), 84);

    int v2[] = {11, 2, 4, 5, 6};
    char s2[] = {'(', '*', '-', '(', '+', '/', ')', ')'};
    setGlobals(v2, s2, 5, 8, 1);
    EXPECT_EQ(evaluate_brackets(11), 17.1666);
}

TEST(bracketsTests, badTests)
{
    int v2[] = {11, 2, 4, 5, 0};
    char s2[] = {'(', '*', '-', '(', '+', '/', ')', ')'};
    setGlobals(v2, s2, 5, 8, 1);
    EXPECT_EXIT(evaluate_brackets(11), testing::ExitedWithCode(1), "");
}