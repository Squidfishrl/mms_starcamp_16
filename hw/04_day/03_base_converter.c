#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int char_to_num(char c);
char num_to_char(int num);
void strrev(char *str);
int base_to_dec(unsigned current_base, char *num);
void dec_to_base(unsigned new_base, int num, char *new_num);

int main (int argc, char *argv[])
{
        int initial_base, new_base;
        char num[32];
        char new_num[32];
        char new_num2[32];
        scanf("%d %s %d", &initial_base, num, &new_base);
        int dec_num = base_to_dec(initial_base, num);
        printf("dec num: %d\n", dec_num);
        dec_to_base(new_base, dec_num, new_num2);
        strrev(new_num2);
        printf("converted num: %s\n", new_num2);

        return 0;
}

int char_to_num(char c)
{
        if ('0' <= c && '9' >= c)
                return c - '0';
        else if ('a' <= c && 'z' >= c)
                return (c - 'a') + 10;
        else if ('A' <= c && 'Z' >= c)
                return (c - 'A') + 10;
        else
                return -1;
}

int base_to_dec(unsigned current_base, char *num)
{
        int new_num = 0;
        int exponent = 0;
        
        for (char i = strlen(num) - 1; i >= ('-' == num[0]); i--) {
                new_num += char_to_num(num[i]) * pow(current_base, exponent++);
        }

        if ('-' == num[0])
                new_num *= -1;

        return new_num;
}

char num_to_char(int num)
{
        if (num < 0)
                return 0;
        else if (num < 10)
                return '0' + num;
        else if (num < 33)
                return 'a' + (num - 10);
        else
                return 0;
}

void dec_to_base(unsigned new_base, int num, char *new_num)
{
        int i = 0;

        if (num < 0) {
                i = 1;
                new_num[0] = '-';
                num = abs(num);
        }

        do {
                int remain = num % new_base; 
                new_num[i++] = num_to_char(remain);
                num /= new_base;
        } while (num > 0);

        new_num[i+1] = '\0';
}

void strrev(char *str)
{
        char *p1, *p2;
        if (!str || !(*str))
                return;

        // preserve upfront negative sign
        for (p1 = '-' == str[0] ? str+1 : str, p2 = str + strlen(str) -1; p2 > p1; p1++, p2--) {
                *p1 ^= *p2;
                *p2 ^= *p1;
                *p1 ^= *p2;
        }
}

