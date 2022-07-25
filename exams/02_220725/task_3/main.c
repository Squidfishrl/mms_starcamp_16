#include <stdio.h>
#include <stdbool.h>

#define DIGITS 500

int encode(char *number);

int main (int argc, char *argv[])
{
        char number[DIGITS];
        for (int i = 0; i < DIGITS; i++) {
                number[i] = '\0';
        }
        fgets(number, DIGITS, stdin);

        if (encode(number) != 0) {
                fprintf(stderr, "error, invalid symbols in number\n");
                return -1;
        }

        printf("%s\n", number);

        
        return 0;
}

int encode(char *number)
{
        // verify digits
        for (int i = 0; i < DIGITS; i++) {
                if (number[i] < '0' || number[i] > '9') {
                        if (number[i] == '\n') {
                                number[i] = '\0';
                                break;
                        } else {
                                return -1;
                        }
                }
        }

        char odd_enc_table[10] = {
                '!',
                '#',
                '/',
                '~',
                '=',
                '`',
                '\\',
                '>',
                '.',
                ','
        };

        for (int i = 0; *number != '\0'; number++, i++) {
                if (0 == i % 2) 
                        *number = *number - '0' + 'A';
                else 
                        *number = odd_enc_table[*number - '0'];

        }

        return 0;
}
