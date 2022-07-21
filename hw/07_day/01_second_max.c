#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int secondMax(const int *arr, size_t n, int *secondMax);
int int_comparator(const void *, const void *);

int main (int argc, char *argv[])
{
        int second_max = INT_MIN;

        int arr[10] = {-1, 8, -5, 3, 22, 67, 4, 12, 9, -5};
        int rtrn_code;
        rtrn_code = secondMax(arr, 10, &second_max);
        if (rtrn_code == -1) 
                fprintf(stderr, "error: array size less than 2\n");
        else if (rtrn_code == -2)
                fprintf(stderr, "warning: all array elements have the same size\n");
        printf("%d\n", second_max);


        second_max = INT_MIN;

        int arr2[1] = {-1};
        rtrn_code = secondMax(arr2, 1, &second_max);
        if (rtrn_code == -1) 
                fprintf(stderr, "error: array size less than 2\n");
        else if (rtrn_code == -2)
                fprintf(stderr, "warning: all array elements have the same size\n");
        printf("%d\n", second_max);

        second_max = INT_MIN;

        int arr3[7] = {1, 1, 1, 1, 1, 1, 1};
        rtrn_code = secondMax(arr3, 7, &second_max);
        if (rtrn_code == -1) 
                fprintf(stderr, "error: array size less than 2\n");
        else if (rtrn_code == -2)
                fprintf(stderr, "warning: all array elements have the same size\n");
        printf("%d\n", second_max);
        
        return 0;
}


int secondMax(const int *arr, size_t n, int *secondMax)
{
        if (n < 2)
                return -1;

        int new_arr[n];
        for (int i = 0; i < n; i++) {
                new_arr[i] = arr[i];
        }

        qsort(new_arr, n, sizeof(new_arr[0]), int_comparator);

        *secondMax = new_arr[1];

        if (new_arr[0] == new_arr[n-1])
                return -2;

        return 0;
}

int int_comparator(const void *a, const void *b)
{
        return *(int *)b - *(int *)a;
}
