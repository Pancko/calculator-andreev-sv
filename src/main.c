#include "main.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int val = 0;
int sym = 0;
int values[SIZE] = {0};
char symbols[SIZE] = {0};
int current_val = 1;
int current_sym = 0;
int is_float = 0;
int prev_symbol = -1; //-1 = start, 0 = num, 1 = symbol

int checkNumSize(double num)
{
    if (num > 2000000000 || num < -2000000000)
    {
        printf("unacceptable number size(>|2 * 10^9|) -> exit(4)\n");
        exit(4);
    }
    return 0;
}

double division(double first, double second)
{
    if (second <= 0.0001 && second >= -0.0001)
    {
        printf("unacceptable div argument(<=|0.0001|) -> exit(1)\n");
        exit(1);
    }
    if (is_float)
        return first / second;
    else
        return (int)(first / second);
}

void parser(char buffer[65536], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (buffer[i] != ' ')
        {
            if (buffer[i] >= 48 && buffer[i] <= 57)
            {
                if (val == SIZE)
                {
                    printf("too much integers -> exit(3)\n");
                    exit(3);
                }
                values[val] = buffer[i] - '0';
                int j = i + 1;
                while (buffer[j] >= 48 && buffer[j] <= 57)
                {
                    values[val] = values[val] * 10 + (buffer[j] - '0');
                    j++;
                }
                i = j - 1;
                // printf("values[%d] = %d\n", val, values[val]); //tests
                checkNumSize(values[val]);
                val++;
                prev_symbol = 0;
            }
            else if (buffer[i] >= 40 && buffer[i] <= 47 && buffer[i] != 44 && buffer[i] != 46)
            {
                if (sym == SIZE)
                {
                    printf("too much symbols -> exit(3)\n");
                    exit(3);
                }
                // printf("symbols[%d] = %d\n", sym, buffer[i]); //tests
                symbols[sym] = buffer[i];

                if (prev_symbol == 1 && symbols[sym] != '(' && symbols[sym - 1] != ')')
                {
                    printf("two special symbols in a row! -> exit(7)\n");
                    exit(7);
                }
                if (prev_symbol != 0 && symbols[sym] == '-')
                {
                    printf("no negative numbers! -> exit(6)\n");
                    exit(6);
                }
                if (prev_symbol == -1 && symbols[sym] != '(')
                {
                    printf("input cant start with this symbol -> exit(8)\n");
                    exit(8);
                }
                sym++;
                prev_symbol = 1;
            }
            else if (buffer[i] != 10 && buffer[i] != '\r' && buffer[i] != '\n' && buffer[i] != '\t' &&
                     buffer[i] != '\f' && buffer[i] != '\v')
            {
                printf("unacceptable symbol -> exit(2)\n");
                exit(2);
            }
        }
    }
}

double zzz(double result)
{
    double res = result;
    char operation = symbols[current_sym];
    if (operation == '(')
    {
        current_sym++;
        return zzz(res);
    }
    // printf ("first = %d, ", res);//test
    // printf ("operation = %d ", operation); //test
    double second = values[current_val];
    // printf (",second = %d ", second);//test
    current_val++;
    if (operation == ')')
    {
        if (current_sym >= 1 && symbols[current_sym - 1] == '(')
            return res;
        current_sym++;
        operation = symbols[current_sym];
    }
    if (current_sym < sym && symbols[current_sym + 1] == '(')
    {
        current_sym++;
        switch (operation)
        {
        case '+':
            return res + zzz(second);
        case '-':
            return res - zzz(second);
        case '*':
            return res * zzz(second);
        case '/':
            return division(res, zzz(second));
        }
    }
    current_sym++;
    switch (operation)
    {
    case '+':
        {
            if (symbols[current_sym] != '*' && symbols[current_sym] != '/')
                return res + second;
            return res + zzz(second);
        }
    case '-':
        {
            if (symbols[current_sym] != '*' && symbols[current_sym] != '/')
                return res - second;
            return res - zzz(second);
        }
    case '*':
        return res * second;
    case '/':
        return division(res, second);
    }
    return res;
}

#ifndef GTEST
int main(int argc, char **argv)
{
    char buffer[65536];
    int len = 0;

    for (int i = 0; i < argc; i++)
        if (strcmp(argv[i], "--float") == 0)
            is_float = 1;
        else
            is_float = 0;

    while (fgets(buffer + len, sizeof(buffer) - len, stdin))
        len += strlen(buffer + len);

    parser(buffer, len);

    double result = 0;
    result = values[0];
    while (current_sym < sym && current_val < val)
    {
        result = zzz(result);
        checkNumSize(result);
        // printf(", result = %.4f\n", result); //tests
    }
    if (is_float == 1)
        printf("%.4f\n", result);
    else
        printf("%.0f\n", result);
    return 0;
}
#endif