#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_arg {
        char *fname;
        int thread_num;
};

void *resort_intbin_file(void *args);
int intcmp(const void *, const void *);

int main (int argc, char *argv[])
{
        pthread_t threads[argc-1];
        struct thread_arg thargs[argc-1];

        for (int i = 0; i < argc - 1; i++)  {
                thargs[i].fname = *(argv+i+1);  
                thargs[i].thread_num = i;
                if (pthread_create(threads+i, NULL, resort_intbin_file, thargs+i)) {
                        perror("pthread_create");
                        return EXIT_FAILURE;
                }
        }

        for (int i = 0; i < argc - 1; i++)  {
                if (pthread_join(threads[i], NULL)) {
                        perror("pthread_join");
                        return EXIT_FAILURE;
                }
        }

        return 0;
}

void *resort_intbin_file(void *args)
{
        struct thread_arg *tharg = (struct thread_arg *)args;

        FILE *fp = fopen(tharg->fname, "wb+");

        int bytes = fseek(fp, 0, SEEK_END);
        if (bytes % 4 != 0) {
                fprintf(stderr, "invalid file");
                exit(EXIT_FAILURE);
        }

        int num_cnt = bytes/4;
        int nums [num_cnt];

        if (fread(nums, sizeof(int), num_cnt, fp) != num_cnt) {
                perror("fread");
                exit(EXIT_FAILURE);
        }

        qsort(nums, num_cnt, sizeof(int), intcmp);

        if (fwrite(nums, sizeof(int), num_cnt, fp) != num_cnt) {
                perror("fwrite");
                exit(EXIT_FAILURE);
        }

        return NULL;
}

int intcmp(const void *num1, const void *num2)
{
        return *(int *)num1 - *(int *)num2;
}
