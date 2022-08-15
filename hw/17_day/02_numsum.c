#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int sum_nums(char **nums, int cnt);

int main (int argc, char *argv[])
{
        int fd1[2];
        int fd2[2];
        if (pipe(fd1)) {
                perror("pipe");
                return EXIT_FAILURE;
        }

        if (pipe(fd2)) {
                perror("pipe");
                return EXIT_FAILURE;
        }

        int sum = 0;
        int p1 = fork();

        if (0 == p1) {
                close(fd1[0]);
                int partial_sum = sum_nums(argv+1, (argc - 1) / 2);
                write(fd1[1], &partial_sum, sizeof(int));

                close(fd1[1]);
                exit(EXIT_SUCCESS);
        }

        int p2 = fork();

        if (0 == p2) {
                close(fd2[0]);
                int partial_sum = sum_nums(argv + 1 + (argc - 1) / 2, (argc - 1) - ((argc - 1) / 2) );
                write(fd2[1], &partial_sum, sizeof(int));
                close(fd2[1]);
                exit(EXIT_SUCCESS);
        }

        wait(NULL);
        close(fd1[1]);
        close(fd2[1]);

        int partial_sum;

        read(fd1[0], &partial_sum, sizeof(int));
        sum += partial_sum;
        close(fd1[0]);

        read(fd2[0], &partial_sum, sizeof(int));
        sum += partial_sum;
        close(fd2[0]);

        printf("Sum -> %d\n", sum);
        
        return 0;
}

int sum_nums(char **nums, int cnt)
{
        int sum = 0;
        for (int i = 0; i < cnt; i++) {
                sum += atoi(*(nums + i));
        }

        return sum;
}
