#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define STR_LEN 10

void *print_rand_msg(void *args);
int randint(int min, int max);

int main (int argc, char *argv[])
{
        if (argc != 2) {
                fprintf(stderr, "Invalid arguments\n");
                return EXIT_FAILURE;
        }

        int thread_count = atoi(argv[1]);
        pthread_t threads[thread_count];
        srand(time(NULL));
        unsigned seeds[thread_count];


        for(int i = 0; i < thread_count; i++) {
                seeds[i] = rand();
                if (pthread_create(threads+i, NULL, print_rand_msg, &seeds[i])) {
                        perror("pthread_create");
                        return EXIT_FAILURE;
                }
        }

        for(int i = 0; i < thread_count; i++) {
                pthread_join(threads[i], NULL);
        }
    
        return EXIT_SUCCESS;
}

void *print_rand_msg(void *args)
{
        unsigned seed = *(unsigned *)args;
        char str[STR_LEN];

        for (int i = 0; i < STR_LEN; i++) {
                str[i] = randint('a', 'z');
        }

        printf("%s\n", str);
        return NULL;
}

inline int randint(int min, int max)
{
        return min + (rand() % (1 + max - min ));
}
