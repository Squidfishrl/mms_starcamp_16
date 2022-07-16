#include <stdio.h>

int rectangle(double w, double h, double *S, double *P);
void clean_stdin();

int main (int argc, char *argv[])
{
        double w, h;
        double S, P;

        int input_code;
        while ( (input_code = scanf("%lf %lf", &w, &h)) != -1) {
                if (input_code != 2) {
                        fprintf(stderr, "error: Invalid argument format\n");
                        // scanf doesn't clear the stdin buffer on invalid formatting - do it manually
                        clean_stdin();
                        continue;
                }

                if (rectangle(w, h, &S, &P) == -1) {
                        fprintf(stderr, "error: Invalid rectangle sides\n");
                        continue;
                }

                printf("S = %.2lf\nP = %.2lf\n", S, P);
        }
        return 0;
}

int rectangle(double w, double h, double *S, double *P)
{
        if (w <= 0 || h <= 0) {
                return -1;
        }

        *P = 2 * (w + h);
        *S = w * h;

        return 0;
}

void clean_stdin()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
                continue;
        }
}
