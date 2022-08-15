#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void do_nothing();

int main (int argc, char *argv[])
{
        struct sigaction sa;
        sa.sa_handler = do_nothing;
        sigaction(SIGINT, &sa, NULL);  // ctrl+c
        sigaction(SIGTSTP, &sa, NULL);  // ctrl+z
        // SIGKILL cannot be masked since it's handled directly by the kernel
    
        while (1) {
                printf("MMS C Camp\n");
                usleep(500000);
        }

        return EXIT_SUCCESS;
}

inline void do_nothing() {
        return;
}
