#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int quadEq(double a, double b, double c, double *x1, double *x2);
void clean_stdin();

int main (int argc, char *argv[])
{
        double a, b, c;
        double x1, x2;

        if (argc != 4) {
                fprintf(stderr, "error: invalid parameter amount\n");
                return -1;
        }

        char *end;
        a = strtod(argv[1], &end);
        if (end == argv[1]) {
                fprintf(stderr, "error: invalid argument\n");
                return -1;
        }

        b = strtod(argv[2], &end);
        if (end == argv[2]) {
                fprintf(stderr, "error: invalid argument\n");
                return -1;
        }

        c = strtod(argv[3], &end);
        if (end == argv[3]) {
                fprintf(stderr, "error: invalid argument\n");
                return -1;
        }

        if (quadEq(a, b, c, &x1, &x2) == -1)
                printf("no real roots\n");
        else
                printf("x1 = %.2lf\nx2 = %.2lf\n", x1, x2);

        return 0;
}

int quadEq(double a, double b, double c, double *x1, double *x2)
{
        double D = pow(b, 2) - 4*a*c;

        if (D < 0) 
                return -1;

        double D_sq = sqrt(D);

        *x1 = (-b + D_sq)/2*a;
        *x2 = (-b - D_sq)/2*a;

        return 0;
}

void clean_stdin()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
                continue;
        }
}
