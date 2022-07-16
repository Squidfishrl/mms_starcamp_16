#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned onesCount(uint64_t mask);

int main (int argc, char *argv[])
{
        printf("%d\n", onesCount(0b01110));
        return 0;
}

unsigned onesCount(uint64_t mask)
{
        unsigned ones_counter = 0;

        for (size_t bit = 0; bit < sizeof(mask) * CHAR_BIT; bit++) {
                ones_counter += !!(mask & (1ull << bit));
        }

        return ones_counter;
}
