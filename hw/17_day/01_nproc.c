#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define STR_LEN 10

int randint(int min, int max);

int main (int argc, char *argv[])
{
        srand(time(NULL));

        if (argc != 2) {
                fprintf(stderr, "Invalid arguments\n");
                return EXIT_FAILURE;
        }

        int processes = atoi(argv[1]);
        unsigned seeds[processes];
        char str[STR_LEN];

        for (int i = 0; i < processes; i++) {
                seeds[i] = rand();
        }

        for (int i = 0; i < processes; i++) {
                int pid = fork();

                if (0 == pid) {
                        srand(seeds[i]);
                        for (int j = 0; j < STR_LEN; j++) {
                                str[j] = randint('a', 'z');
                        }

                        printf("Thread %d -> %s\n", i, str);
                        exit(EXIT_SUCCESS);
                }
        }
        
        wait(NULL);

        return EXIT_SUCCESS;
}

inline int randint(int min, int max)
{
        return min + (rand() % (min - max + 1));
}
