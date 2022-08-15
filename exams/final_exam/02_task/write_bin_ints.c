#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define INT_CNT 100

int main (int argc, char *argv[])
{
        srand(time(NULL));
        uint32_t ints[INT_CNT];

        while (*++argv != NULL) {
                FILE *fp = fopen(*argv, "wb");
                if (NULL == fp) {
                        perror("fopen");
                        return EXIT_FAILURE;
                }

                for(int i = 0; i < INT_CNT; i++) {
                        ints[i] = rand();
                }

                if (fwrite(ints, sizeof(int), INT_CNT, fp) != INT_CNT) {
                        perror("fwrite");
                        return EXIT_FAILURE;
                }

                if (fclose(fp)) {
                        perror("fclose");
                        return EXIT_FAILURE;
                }
        }

        return EXIT_SUCCESS;
}
