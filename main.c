#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int val = 0;
int sym = 0;
int values[16];
char symbols[16];
int current_val = 1;
int current_sym = 0;

int zzz(int result)
{
    int res = result;
    char operation = symbols[current_sym];
    if (operation == '(')
    {
        current_sym++;
        return zzz(res);
    }
    //printf ("first = %d, ", res);test
    //printf ("operation = %d ", operation); test
    int second = values[current_val];
    //printf (",second = %d ", second);test
    current_val ++;
    if (operation == ')')
    {
        current_sym ++;
        operation = symbols[current_sym];
    }
    if (current_sym < sym && symbols[current_sym + 1] == '(')
    {
        current_sym++;
        if (operation == '+'){
            return res + zzz(second);
        }
        else if (operation == '-') {
            return res - zzz(second);
        }
        else if (operation == '*') {
            return res * zzz(second);
        }
        else if (operation == '/') {
            return res / zzz(second);
        }
    }
    current_sym++;
    if (operation == '+'){
        if (symbols[current_sym] != '*' && symbols[current_sym] != '/')
            return res + second;
        return res + zzz(second);
    }
    else if (operation == '-') {
        if (symbols[current_sym] != '*' && symbols[current_sym] != '/')
            return res - second;
        return res - zzz(second);
    }
    else if (operation == '*') {
        return res * second;
    }
    else if (operation == '/') {
        return res / second;
    }
}

int main()
{
    int result = 0;
    char buffer[65536];
    size_t len = 0;
    while (fgets(buffer + len, sizeof(buffer) - len, stdin)) {
        len += strlen(buffer + len);
    }

    for (int i = 0; i < len; i++)
    {
        if (buffer[i] != ' ')
        {
            if (buffer[i] >= 48 && buffer[i] <= 57)
            {
                values[val] = buffer[i] - '0';
                int j = i + 1;
                while(buffer[j] >= 48 && buffer[j] <= 57)
                {
                    values[val] = values[val] * 10 + (buffer[j] - '0');
                    j++;
                    i = j;
                }
                val++;
            } 
            else if (buffer[i] >= 40 && buffer[i] <= 47 && buffer[i] != 44 && buffer[i] != 46)
            {
                symbols[sym] = buffer[i];
                sym++;
            }
            else if (buffer[i] != 10) return -1;
        }
    }

    result = values[0];
    while (current_sym < sym && current_val < val)
    {
        result = zzz(result);
        //printf(", result = %d\n", result); tests
    }
    printf("%d", result);
    return 0;
}