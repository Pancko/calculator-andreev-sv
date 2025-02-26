#include "../../src/main.h"
#include <gtest/gtest.h>

extern "C"
{
    double evaluate_brackets(double init);
    double zzz(double result);
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

int v[SIZE] = {0};
char s[SIZE] = {0};
TEST(zzzTests, goodTests)
{
    v[0] = 11;
    v[1] = 3;
    s[0] = '*';
    setGlobals(v, s, 3, 2, 0);
    EXPECT_EQ(zzz(11), 33);

    s[0] = '(';
    s[1] = '+';
    s[2] = ')';
    setGlobals(v, s, 3, 3, 0);
    EXPECT_EQ(zzz(11), 14);

    v[1] = 4;
    s[0] = '/';
    setGlobals(v, s, 3, 1, 0);
    EXPECT_EQ(zzz(11), 2);

    setGlobals(v, s, 3, 1, 1);
    EXPECT_EQ(zzz(11), 2.75);
}

TEST(zzzTests, badTests)
{
    v[0] = 11;
    v[1] = 0;
    s[0] = '/';
    setGlobals(v, s, 2, 1, 0);
    EXPECT_EXIT(zzz(11), testing::ExitedWithCode(1), "");

    v[0] = 11;
    v[1] = 0.0001;
    setGlobals(v, s, 2, 1, 0);
    EXPECT_EXIT(zzz(11), testing::ExitedWithCode(1), "");
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
    EXPECT_EQ(evaluate_brackets(11), 17.166666666666668);
}

TEST(bracketsTests, badTests)
{
    int v2[] = {11, 2, 4, 5, 0};
    char s2[] = {'(', '*', '-', '(', '+', '/', ')', ')'};
    setGlobals(v2, s2, 5, 8, 1);
    EXPECT_EXIT(evaluate_brackets(11), testing::ExitedWithCode(1), "");
}