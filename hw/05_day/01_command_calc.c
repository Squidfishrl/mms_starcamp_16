#include <stdio.h>

void clean_stdin();

int main (int argc, char *argv[])
{
        double num1, num2;
        char operator;

        int input_code;
        while ( (input_code = scanf("%lf %c %lf", &num1, &operator, &num2)) != -1) {
                double res;

                if (input_code != 3) {
                        fprintf(stderr, "error: Invalid argument format\n");
                        // scanf doesn't clear the stdin buffer on invalid formatting - do it manually
                        clean_stdin();
                        continue;
                }

                switch (operator) {
                case '+':
                        res = num1 + num2;
                        break;
                case '-':
                        res = num1 - num2;
                        break;
                case '*':
                        res = num1 * num2;
                        break;
                case '/':
                case ':':
                        res = num1 / num2;
                        break;
                default:
                        fprintf(stderr, "error: Invalid operator\n");
                        continue;
                }

                printf("%.2lf\n", res);
        }

        return 0;
}

void clean_stdin()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
                continue;
        }
}
