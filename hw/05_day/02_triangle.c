#include <stdio.h>
#include <math.h>

int triangle(double a, double b, double c, double *S, double *P);
void clean_stdin();

int main (int argc, char *argv[])
{
        double a, b, c;
        double S, P;

        int input_code;
        while ( (input_code = scanf("%lf %lf %lf", &a, &b, &c)) != -1) {
                if (input_code != 3) {
                        fprintf(stderr, "error: Invalid argument format\n");
                        // scanf doesn't clear the stdin buffer on invalid formatting - do it manually
                        clean_stdin();
                        continue;
                }

                if (triangle(a, b, c, &S, &P) == -1) {
                        fprintf(stderr, "error: Invalid triangle sides\n");
                        continue;
                }

                printf("S = %.2lf\nP = %.2lf\n", S, P);
        }
        return 0;
}

int triangle(double a, double b, double c, double *S, double *P)
{
        if (a <= 0 || b <= 0 || c <= 0) {
                return -1;
        }

        if (a + b < c || a + c < b || b + c < a) {
                return -1;
        }

        *P = a + b + c;

        double p = *P / 2;
        *S = sqrt(p * (p-a) * (p-b) * (p-c));

        return 0;
}

void clean_stdin()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
                continue;
        }
}
