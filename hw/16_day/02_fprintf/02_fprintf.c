#include <math.h>
#include <unistd.h>
#include "ffprint.h"

int main (int argc, char *argv[])
{
        int a = 10;
        char c = 'h';
        char *s = "string test";
        ffprint(STDOUT_FILENO, "int -> %d\nfloat -> %f\nchar -> %c\nstring -> %s\nworks!\n", a, M_PI, c, s);
        return 0;
}
