#include <stdio.h>
#include <stdint.h>
#include <limits.h>

unsigned zerosCount(uint64_t mask1, uint32_t mask2, uint16_t mask3, uint8_t mask4);
void flipOddBits(uint64_t *mask);
void mirrorBits(uint16_t *mask);
void print_bits(uint64_t mask);

int main (int argc, char *argv[])
{
        printf("%d\n", zerosCount(0b0001, 0b0011, 0b0101, 0b0000));  // 115

        uint64_t mask = 0;
        flipOddBits(&mask);
        print_bits(mask);  // 0b1010101010101010101010101010101010101010101010101010101010101010 

        uint16_t mask2 = UINT16_MAX - 123;
        mirrorBits(&mask2);
        printf("%d\n", mask2);  // 123
        
        return 0;
}

unsigned zerosCount(uint64_t mask1, uint32_t mask2, uint16_t mask3, uint8_t mask4)
{
        unsigned zero_counter = 0;

        for (size_t i = 0; i < sizeof(mask1) * CHAR_BIT; i++) {
                zero_counter += !(mask1 & (1ull << i));

                if (i < sizeof(mask2) * CHAR_BIT) {
                        zero_counter += !(mask2 & (1ull << i));

                        if (i < sizeof(mask3) * CHAR_BIT) {
                                zero_counter += !(mask3 & (1 << i));

                                if (i < sizeof(mask4) * CHAR_BIT) {
                                        zero_counter += !(mask4 & (1 << i));
                                }
                        }
                }
        }

        return zero_counter;
}

void flipOddBits(uint64_t *mask)
{
        for (size_t i = 1; i < sizeof(*mask) * CHAR_BIT; i++) {
                *mask ^= (1ull << ++i);
        }
}

void print_bits(uint64_t mask)
{
        printf("0b");
        for (size_t i = 0; i < sizeof(mask) * CHAR_BIT; i++) {
                printf("%d", !!(mask & (1ull << i)));
        }
        putchar('\n');
}

void mirrorBits(uint16_t *mask)
{
        *mask ^= -1;
}
