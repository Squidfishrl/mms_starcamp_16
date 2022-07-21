#include <stdio.h>
#include <stdint.h>

#define TINT    1
#define TCHAR   2
#define TDOUBLE 3
#define TFLOAT  4
#define TUINT8  5
#define TUINT16 6
#define TUINT32 7
#define TUINT64 8

void printValue(const void *valuePtr, uint8_t flag);

int main (int argc, char *argv[])
{
        double val = 3.14;
        printValue(&val, TDOUBLE);
        uint16_t val2 = 4430;
        printValue(&val2, TUINT16);

        return 0;
}

void printValue(const void *valuePtr, uint8_t flag)
{
        switch(flag) {
        case TINT:
                printf("Value: %d\n", *(int *)valuePtr);
                break;
        case TCHAR:
                printf("Value: %c\n", *(char *)valuePtr);
                break;
        case TDOUBLE:
                printf("Value: %lf\n", *(double *)valuePtr);
                break;
        case TFLOAT:
                printf("Value: %f\n", *(float*)valuePtr);
                break;
        case TUINT8:
                printf("Value: %uh\n", *(uint8_t *)valuePtr);
                break;
        case TUINT16:
                printf("Value: %hu\n", *(uint16_t *)valuePtr);
                break;
        case TUINT32:
                printf("Value: %ud\n", *(uint32_t *)valuePtr);
                break;
        case TUINT64:
                printf("Value: %lu\n", *(uint64_t *)valuePtr);
                break;
        default:
                fprintf(stderr, "error: invalid flag\n");
        }
}
