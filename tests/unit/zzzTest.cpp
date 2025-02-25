#include <gtest/gtest.h>
#include "../../src/main.h"

extern "C" 
{
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
    v[0] = 11; v[1] = 3;
    s[0] = '*';
    setGlobals(v,s,3,2,0);
    EXPECT_EQ(zzz(11),33);

    s[0] = '('; s[1] = '+'; s[2] = ')';
    setGlobals(v,s,3,3,0);
    EXPECT_EQ(zzz(11),14);

    v[1] = 4;
    s[0] = '/';
    setGlobals(v,s,3,1,0);
    EXPECT_EQ(zzz(11),2);

    setGlobals(v,s,3,1,1);
    EXPECT_EQ(zzz(11),2.75);
}

TEST(zzzTests, badTests)
{
    v[0] = 11; v[1] = 0;
    s[0] = '/';
    setGlobals(v,s,2,1,0);
    EXPECT_EXIT(zzz(11), testing::ExitedWithCode(1), "");

    v[0] = 11; v[1] = 0.0001;
    setGlobals(v,s,2,1,0);
    EXPECT_EXIT(zzz(11), testing::ExitedWithCode(1), "");
}