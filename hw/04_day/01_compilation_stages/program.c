#include <stdio.h>

void swap(int *, int *);

int main (void)
{
        int num1, num2;        
        printf("Enter first numer: ");
        scanf("%d", &num1);
        printf("Enter second numer: ");
        scanf("%d", &num2);
        printf("Before swap: Num1 = %d, Num2 = %d\n", num1, num2);
        swap(&num1, &num2);
        printf("After swap: Num1 = %d, Num2 = %d\n", num1, num2);
        return 0;
}
