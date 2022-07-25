
#include <stdio.h>
#include <stdlib.h>
#include "comparators.h"

double rand_double(double min, double max);

int main (int argc, char *argv[])
{

#if (defined COUNT) && (defined MAX) && (defined MIN)
        double num_arr[COUNT];

        printf("Generating array\n");
        for (int i = 0; i < COUNT; i++) {
                num_arr[i] = rand_double(MIN, MAX);
                printf("%lf ", num_arr[i]);
        }
        putchar('\n');

        int (*comparators[])(const void *, const void *) = {
                comp_asc,
                comp_desc,
                comp_whole_digit_acucmulator,
                comp_abs
        };

        printf(
                "0 - ascending\n"
                "1 - descending\n"
                "2 - digit accumulator\n"
                "3 - absolute value\n"
                "Choose comparator: "
        );


        int comp_option;
        if (scanf("%d", &comp_option) != 1) {
                fprintf(stderr, "error: invalid parameter");
                return -1;
        }

        qsort(num_arr, COUNT, sizeof(num_arr[0]), comparators[comp_option]);

        printf("Sorted array\n");
        for (int i = 0; i < COUNT; i++) {
                printf("%lf ", num_arr[i]);
        }
        putchar('\n');

        return 0;
#else // (defined COUNT) && (defined MAX) && (defined MIN)
        fprintf(stderr, "error: definitions missing");
        return -1;
#endif // (defined COUNT) && (defined MAX) && (defined MIN)

}

double rand_double(double min, double max)
{
        return min + (rand() / (double) RAND_MAX) * (max - min);
}

