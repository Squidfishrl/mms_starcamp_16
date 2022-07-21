#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

unsigned bitsNCount(unsigned count, unsigned bitscnt, ...);
unsigned ones_in_mask(int mask);

int main (int argc, char *argv[])
{
        printf("%d\n", bitsNCount(4, 2, 0x0a, 0xff, 0, 1));
        printf("%d\n", bitsNCount(3, 8, 0xff, 0x13f1, 0xaaaa));
        printf("%d\n", bitsNCount(5, 10, 0x0a, 0xa0ff, 0, 10, 0b1010111110111));
        return 0;
}

unsigned bitsNCount(unsigned count, unsigned bitscnt, ...)
{
        unsigned bit_mask_count = 0;

        va_list args;
        va_start(args, bitscnt);

        for (int i = 0; i < count; i++) {
                bit_mask_count += bitscnt == ones_in_mask(va_arg(args, int));
        }

        va_end(args);

        return bit_mask_count;
}

unsigned ones_in_mask(int mask)
{
        int ones = 0;

        for (int i = 0; i < sizeof(mask) * CHAR_BIT; i++) {
                ones += !!(mask & (1 << i));
        }

        return ones;
}
