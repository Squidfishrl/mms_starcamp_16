#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

// count == amount of masks
size_t onesCount(size_t count, ...);
size_t ones_in_mask(int mask);

int main (int argc, char *argv[])
{
        printf("%lu\n", onesCount(4, 0x0a, 0, 1, 2));
        printf("%lu\n", onesCount(3, 0xff, 0x131, 0xaaaa));
        printf("%lu\n", onesCount(2, 0b0001, 9));
        return 0;
}

size_t onesCount(size_t count, ...)
{
        size_t ones_counter = 0;

        va_list args;
        va_start(args, count);

        for (size_t i = 0; i < count; i++) {
                int mask = va_arg(args, int);
                ones_counter += ones_in_mask(mask);
        }

        va_end(args);
        return ones_counter;
}

size_t ones_in_mask(int mask)
{
        size_t ones_counter = 0;

        for (size_t i = 0; i < sizeof(mask) * CHAR_BIT; i++) {
                ones_counter += !!(mask & (1 << i));
        }

        return ones_counter;
}
