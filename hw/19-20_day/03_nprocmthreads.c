#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>
#include <time.h>

#define MSG_LEN 10

struct tharg {
        int process_num;
        int thread_num;
};

void *print_msg(void *args);
int randint(int min, int max);

int main (int argc, char *argv[])
{
        int opt;
        int proc_cnt = 5;
        int thread_cnt = 6;
        while ((opt = getopt(argc, argv, ":p:t:")) != -1) {
                switch (opt) {
                case 'p':
                        proc_cnt = atoi(optarg);
                        break;
                case 't':
                        thread_cnt = atoi(optarg);
                        break;
                }
        }
        
        pthread_t threads[thread_cnt];
        unsigned seeds[proc_cnt];
        struct tharg thargs[thread_cnt];
        srand(time(NULL));

        for (int i = 0; i < proc_cnt; i++) {
                seeds[i] = rand();

                int pid = fork();

                if (-1 == pid) {
                        perror("fork");
                        exit(EXIT_FAILURE);
                }

                if (0 == pid) {
                        srand(seeds[i]);

                        for (int j = 0; j < thread_cnt; j++) {
                                struct tharg tharg = {.process_num = i, .thread_num = j};
                                thargs[j] = tharg;
                                if (pthread_create(threads+j, NULL, print_msg, thargs+j)) {
                                        perror("pthread_create");
                                        exit(EXIT_FAILURE);
                                }
                        }

                        for (int j = 0; j < thread_cnt; j++) {
                                if (pthread_join(threads[j], NULL)) {
                                        perror("pthread_create");
                                        exit(EXIT_FAILURE);
                                }
                        }

                        exit(EXIT_SUCCESS);
                }
        }

        wait(NULL);
        return 0;
}

void *print_msg(void *args)
{
        struct tharg *tharg = (struct tharg *)args;

        char str[MSG_LEN];
        for (int i = 0; i < MSG_LEN; i++) {
                str[i] = randint('a', 'z');
        }

        printf("Proccess - %d  Thread - %d  MSG - %s\n", tharg->process_num, tharg->thread_num, str);
        return NULL;
}

inline int randint(int min, int max)
{
        return min + (rand() % (1 + max - min));
}
