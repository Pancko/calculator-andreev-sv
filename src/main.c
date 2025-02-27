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
    int brackets = 0;
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
                if (prev_symbol == 0)
                {
                    printf("no signs between two integers! -> exit(10)\n");
                    exit(10);
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
                switch (symbols[sym])
                {
                case '(':
                    {
                        brackets++;
                        break;
                    }
                case ')':
                    {
                        if (brackets > 0)
                            brackets--;
                        else
                        {
                            printf("brackets not correct! -> exit(9)\n");
                            exit(9);
                        }
                        break;
                    }
                }

                if (prev_symbol == 1 && symbols[sym] != '(' && symbols[sym - 1] != ')')
                {
                    printf("two special symbols in a row! -> exit(7)\n");
                    exit(7);
                }
                if (prev_symbol != 0 && symbols[sym] == '-' && symbols[sym - 1] != ')')
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
    if (brackets != 0)
    {
        printf("brackets not correct! -> exit(9)\n");
        exit(9);
    }
}

double evaluate_brackets(double res);
double zzz(double init)
{
    double res = init;
    while (current_sym < sym && current_val < val)
    {
        char operation = symbols[current_sym];
        if (operation == ')')
        {
            // printf("brres = %.4f\n", res);
            return res;
        }
        if (operation == '(')
        {
            current_sym++;
            res = evaluate_brackets(res);
            operation = symbols[current_sym];
        }
        double second = values[current_val];
        current_val++;
        if (current_sym < sym && symbols[current_sym + 1] == '(')
        {
            current_sym += 2;
            switch (operation)
            {
            case '*':
                {
                    res *= evaluate_brackets(second);
                    break;
                }
            case '/':
                {
                    res = division(res, evaluate_brackets(second));
                    break;
                }
            default:
                {
                    double brackets = evaluate_brackets(second);
                    while (current_sym < sym && symbols[current_sym] != ')' &&
                           (symbols[current_sym] == '*' || symbols[current_sym] == '/'))
                    {
                        char next_op = symbols[current_sym];
                        current_sym++;
                        if (next_op == '*')
                        {
                            if (symbols[current_sym] == '(')
                            {
                                current_sym++;
                                brackets *= evaluate_brackets(values[current_val]);
                            }
                            else
                            {
                                brackets *= values[current_val];
                                current_val++;
                            }
                        }
                        else
                        {
                            if (symbols[current_sym] == '(')
                            {
                                current_sym++;
                                brackets = division(brackets, evaluate_brackets(values[current_val]));
                            }
                            else
                            {
                                brackets = division(brackets, values[current_val]);
                                current_val++;
                            }
                        }
                    }

                    if (operation == '+')
                    {
                        res += brackets;
                    }
                    else
                    {
                        res -= brackets;
                    }
                    break;
                }
            }
        }
        else
        {
            current_sym++;
            switch (operation)
            {
            case '+':
                {
                    if (symbols[current_sym] != '*' && symbols[current_sym] != '/')
                        res += second;
                    else
                        res += zzz(second);
                    break;
                }
            case '-':
                {
                    if (symbols[current_sym] != '*' && symbols[current_sym] != '/')
                        res -= second;
                    else
                        res -= zzz(second);
                    break;
                }
            case '*':
                {
                    res *= second;
                    break;
                }
            case '/':
                {
                    res = division(res, second);
                    break;
                }
            }
        }
    }
    // printf("res = %.4f\n", res);
    return res;
}

double evaluate_brackets(double init)
{
    double result = init;

    while (current_sym < sym && symbols[current_sym] != ')')
    {
        char op = symbols[current_sym];
        current_sym++;
        if (op == '(')
        {
            result = evaluate_brackets(result);
        }
        else if (current_sym < sym && symbols[current_sym] == '(')
        {
            double second = values[current_val];
            current_val++;
            current_sym++;
            switch (op)
            {
            case '*':
                {
                    result *= evaluate_brackets(second);
                    break;
                }
            case '/':
                {
                    result = division(result, evaluate_brackets(second));
                    break;
                }
            default:
                {
                    double brackets = evaluate_brackets(second);
                    while (current_sym < sym && symbols[current_sym] != ')' &&
                           (symbols[current_sym] == '*' || symbols[current_sym] == '/'))
                    {
                        char next_op = symbols[current_sym];
                        current_sym++;
                        double new_val = values[current_val];
                        current_val++;
                        if (next_op == '*')
                        {
                            if (symbols[current_sym] == '(')
                            {
                                current_sym++;
                                brackets *= evaluate_brackets(new_val);
                            }
                            else
                            {
                                brackets *= new_val;
                            }
                        }
                        else
                        {
                            if (symbols[current_sym] == '(')
                            {
                                current_sym++;
                                brackets = division(brackets, evaluate_brackets(new_val));
                            }
                            else
                            {
                                brackets = division(brackets, new_val);
                            }
                        }
                    }

                    if (op == '+')
                    {
                        // printf("%.4f + %.4f = ", result, brackets);
                        result += brackets;
                        // printf("%.4f\n", result);
                    }
                    else
                    {
                        // printf("%.4f - %.4f = ", result, brackets);
                        result -= brackets;
                        // printf("%.4f\n", result);
                    }
                    break;
                }
            }
        }
        else
        {
            double next_val = values[current_val];
            current_val++;

            switch (op)
            {
            case '*':
                {
                    result *= next_val;
                    break;
                }
            case '/':
                {
                    result = division(result, next_val);
                    break;
                }
            default:
                {
                    while (current_sym < sym && symbols[current_sym] != ')' &&
                           (symbols[current_sym] == '*' || symbols[current_sym] == '/'))
                    {
                        char next_op = symbols[current_sym];
                        current_sym++;
                        if (next_op == '*')
                        {
                            next_val *= values[current_val];
                        }
                        else
                        {
                            next_val = division(next_val, values[current_val]);
                        }
                        current_val++;
                    }

                    if (op == '+')
                    {
                        result += next_val;
                    }
                    else
                    {
                        result -= next_val;
                    }
                    break;
                }
            }
        }
        checkNumSize(result);
    }

    if (current_sym < sym && symbols[current_sym] == ')')
    {
        current_sym++;
    }

    // printf("brackets res = %.4f\n", result);
    return result;
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
    result = zzz(result);
    checkNumSize(result);
    if (is_float == 1)
        printf("%.4f\n", result);
    else
        printf("%.0f\n", result);
    return 0;
}
#endif