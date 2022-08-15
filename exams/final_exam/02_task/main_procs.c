#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>

int print_file_bin_ones(void *args);
uint8_t int32_bin_ones(uint32_t num);

int main (int argc, char *argv[])
{
        if (1 == argc) {
                fprintf(stderr, "Invalid arguments\n");
                return EXIT_FAILURE;
        }

        argv++;
        argc--;

        for (int i = 0; i < argc; i++) {
                int pid = fork();

                if (-1 == pid) {
                        perror("fork");
                        return EXIT_FAILURE;
                }

                if (0 == pid) {
                        // child
                        if (print_file_bin_ones(*(argv+i)) == EXIT_FAILURE) {
                                perror("print_file_bin_ones");
                                exit(EXIT_FAILURE);
                        }

                        exit(EXIT_SUCCESS);
                }
        }

        int wstatus;
        if (wait(&wstatus) == -1) {
                perror("wait");
                return EXIT_FAILURE;
        }

        if (!WIFEXITED(wstatus)) {
                fprintf(stderr, "child process terminatation error\n");
                return EXIT_FAILURE;
        }

        if (WEXITSTATUS(wstatus) == EXIT_FAILURE) {
                fprintf(stderr, "print_file_bin_ones error");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int print_file_bin_ones(void *args)
{
        char *fname = (char *)args;
        FILE *fp = fopen(fname, "rb");
        if (NULL == fp)
                return EXIT_FAILURE;


        int ones_cnt = 0;
        uint32_t num_buf;

        while(fread(&num_buf, sizeof(int), 1, fp) == 1) {
                ones_cnt += int32_bin_ones(num_buf);
        }

        if (!feof(fp) || ferror(fp))
                return EXIT_FAILURE;

        if (fclose(fp))
                return EXIT_FAILURE;

        printf("%s - %d\n", fname, ones_cnt);

        return EXIT_SUCCESS;
}

uint8_t int32_bin_ones(uint32_t num)
{
        uint8_t ones_cnt = 0;

        for (uint8_t i = 0; i < sizeof(num) * CHAR_BIT; i++) {
                ones_cnt += ((num & (1 << i)) != 0);
        }

        return ones_cnt;
}
