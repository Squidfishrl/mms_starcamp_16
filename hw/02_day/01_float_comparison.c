#include <stdio.h>
#include <math.h>

int double_comparison(double a, double b);

int main (int argc, char *argv[])
{
    double a, b, c;

    while(scanf("%lf %lf %lf", &a, &b, &c) != -1) {
        printf("%.3lf\n", fmax(c, fmax(a, b)));
    }
    
    return 0;
}
