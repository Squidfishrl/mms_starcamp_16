#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <limits.h>

void *print_file_bin_ones(void *args);
uint8_t int32_bin_ones(uint32_t num);

int main (int argc, char *argv[])
{
        if (1 == argc) {
                fprintf(stderr, "Invalid arguments\n");
                return EXIT_FAILURE;
        }

        pthread_t threads[argc-1];

        argv++;
        argc--;

        for (int i = 0; i < argc; i++) {
                if (pthread_create(threads+i, NULL, print_file_bin_ones, *(argv+i))) {
                        perror("pthread_create");
                        return EXIT_FAILURE;
                }
        }

        for (int i = 0; i < argc; i++) {
                int rtn_val;
                if (pthread_join(threads[i], (void *) &rtn_val)) {
                        perror("pthread_join");
                        return EXIT_FAILURE;
                }

                if (rtn_val) {
                        perror("print_file_bin_ones");
                        return EXIT_FAILURE;
                }
        }

        return EXIT_SUCCESS;
}

void *print_file_bin_ones(void *args)
{
        char *fname = (char *)args;
        FILE *fp = fopen(fname, "rb");
        if (NULL == fp)
                pthread_exit((void *)EXIT_FAILURE);


        int ones_cnt = 0;
        uint32_t num_buf;

        while(fread(&num_buf, sizeof(int), 1, fp) == 1) {
                ones_cnt += int32_bin_ones(num_buf);
        }

        if (!feof(fp) || ferror(fp))
                pthread_exit((void *)EXIT_FAILURE);

        if (fclose(fp))
                pthread_exit((void *)EXIT_FAILURE);

        printf("%s - %d\n", fname, ones_cnt);

        pthread_exit(NULL);
}

uint8_t int32_bin_ones(uint32_t num)
{
        uint8_t ones_cnt = 0;

        for (uint8_t i = 0; i < sizeof(num) * CHAR_BIT; i++) {
                ones_cnt += ((num & (1 << i)) != 0);
        }

        return ones_cnt;
}
