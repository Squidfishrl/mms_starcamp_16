#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
        if (argc != 3) {
                fprintf(stderr, "Invalid arguments\n");
                return EXIT_FAILURE;
        }

        for (int i = 0; i < 2; i++) {
                int pid = fork();

                if (0 == pid ) {
                        execlp(argv[i+1], argv[i+1], NULL);
                }

                int wstatus;
                wait(&wstatus);

                if (!WIFEXITED(wstatus)) {
                        perror("wait");
                        return EXIT_FAILURE;
                }

                if (WEXITSTATUS(wstatus) != 0) {  // exit status failed
                        break;
                }
        }


        return EXIT_SUCCESS;
}
