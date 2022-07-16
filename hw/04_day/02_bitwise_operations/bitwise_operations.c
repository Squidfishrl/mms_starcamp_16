#include "bitwise_operations.h"

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int add_attendance(uint32_t *attendance, int student_num)
{
        if (student_num > sizeof(*attendance) * CHAR_BIT)
                return -1;

        *attendance |= (1 << student_num);
        return 0;
}

int remove_attendance(uint32_t *attendance, int student_num)
{
        if (student_num > sizeof(*attendance) * CHAR_BIT)
                return -1;

        *attendance &= ~(1lu << student_num);
        return 0;
}

void print_non_attendants(uint32_t attendance)
{
        for (size_t bit = 0; bit < sizeof(attendance) * CHAR_BIT; bit++) {
                if (!(attendance & (1lu << bit)))
                        printf("%lu ", bit);
        }

        putchar('\n');
}

void print_attendants(uint32_t attendance)
{
        for (size_t bit = 0; bit < sizeof(attendance) * CHAR_BIT; bit++) {
                if (attendance & (1lu << bit))
                        printf("%lu ", bit);
        }
        putchar('\n');
}

int change_attendance(uint32_t *attendance, int student_num)
{
        if (student_num > sizeof(*attendance) * CHAR_BIT)
                return -1;

        *attendance ^= (1lu << student_num);
        return 0;
}
