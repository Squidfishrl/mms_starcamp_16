#include <stdio.h>
#include <stdlib.h>

unsigned sumArrayDigits(const int *arr, size_t n);
unsigned sum_num_digits(int num);

int main (int argc, char *argv[])
{
        int arr[5] = {12, 3, 45, 567, 8000}; // 41
        printf("%d\n", sumArrayDigits(arr, 5));

        return 0;
}

unsigned sumArrayDigits(const int *arr, size_t n)
{
        int sum = 0;
        for (int i = 0; i < n; i++) {
                sum += sum_num_digits(arr[i]);
        }
        
        return sum;
}

unsigned sum_num_digits(int num)
{
        int sum = 0;

        for(num = abs(num); num > 0; num /= 10) {
                sum += num % 10;
        }

        return sum;
}
