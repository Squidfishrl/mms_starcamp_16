#include <stdio.h>

#define xor(a, b)(((a) || (b)) && !((a) && (b)))

int main (int argc, char *argv[])
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", xor(a, b));

    return 0;
}
