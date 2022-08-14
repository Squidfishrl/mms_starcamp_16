#include <stdio.h>
#include <stdlib.h>

#define RW_SIZE 100

int main (int argc, char *argv[])
{
        if (argc != 3) {
                fprintf(stderr, "Invalid arguments\n");
        }

        char buff[RW_SIZE];

        FILE *fp_r = fopen(argv[1], "r");
        FILE *fp_w = fopen(argv[2], "w");
        int bytes;

        while ((bytes = fread(buff, sizeof(char), RW_SIZE, fp_r)) > 0) {
                if (fwrite(buff, sizeof(char), bytes, fp_w) != bytes) {
                        perror("fwrite");
                        return EXIT_FAILURE;
                }
        }

        if (!feof(fp_r)) {
                perror("fread");
                return EXIT_FAILURE;
        }


        fclose(fp_r);
        fclose(fp_w);
}
