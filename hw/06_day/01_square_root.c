#include <stdio.h>

int square_root(double num, double *res, int precision);

int main ()
{
        double res;

        if (0 != square_root(3, &res, 10)) {
                fprintf(stderr, "error occured!");
                return -1;
        }

        printf("%.10lf", res);

    
        return 0;
}


int square_root(double num, double *res, int precision)
{
        if (num < 0) {
                return -1;
        } else if (num == 0) {
                 *res = 0;
                 return 0;
        }

        // find integer part 
        double start = 0;
        double end = num;
        double middle;

        while (start < end) {
                 middle = start+end / 2;
                double middle_sqr = middle * middle;

                if (middle_sqr == num) {
                        *res = middle;
                        return 0;
                } else if (middle_sqr < num) {
                        end = middle-1;
                } else {
                        start = middle+1;
                }
        }

        *res = middle;

        double increment_step = 0.1;

        // calc floating part
        for (int i = 0; i < precision; i++) {
                double increment = increment_step;

                while ((*res + increment) * (*res + increment) < num) {
                        increment += increment_step;
                }

                if ((*res + increment) * (*res + increment) == num) {
                        *res += increment;
                        return 0;
                }
                        
                *res += increment - increment_step;
                increment_step /= 10;
        }

        return 0;

}
