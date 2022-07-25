#include "comparators.h"
#include <math.h>
#include <stdlib.h>

int comp_asc(const void *a, const void *b)
{
        double num1 = *(double *) a;
        double num2 = *(double *) b;

        if (fabs(num1 - num2) < ZERO_THRESHOLD)
                return 0;

        return num1 - num2;
}
int comp_desc(const void *a, const void *b)
{
        double num1 = *(double *) a;
        double num2 = *(double *) b;

        if (fabs(num2 - num1) < ZERO_THRESHOLD)
                return 0;

        return num2 - num1;
}

int digit_sum(int num)
{
        int sum = 0;

        for (num = abs(num); num != 0; num /= 10) {
                sum += num % 10;
        }

        return sum;
}

int comp_whole_digit_acucmulator(const void *a, const void *b)
{

        return digit_sum(*(double *) a) - digit_sum(*(double *) b);
}

int comp_abs(const void *a, const void *b)
{
        double num1 = fabs(*(double *) a);
        double num2 = fabs(*(double *) a);

        return comp_asc((const void *)&num1, (const void *)&num2);
}
