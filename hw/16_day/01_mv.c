#include <stdio.h>

int main (int argc, char *argv[])
{
        if (argc != 3) {
                fprintf(stderr, "Invalid arguments\n");
                return -1;
        }

        if (rename(argv[1], argv[2])) {
                perror("rename");
                return -1;
        }

        return 0;
}
