#include <stdio.h>
#include <stdlib.h>

#include "cll.h"

void clear_stdin();

int main (int argc, char *argv[])
{
        int iret_code; 
        int val;

        unsigned int nums = 0;
        unsigned int num_count;

        if (1 != scanf("%ud", &num_count) || num_count < 1) {
                fprintf(stderr, "Error: Invalid argument\n");
                return -1;
        }

        struct Node *cll = NULL;

        while (nums < num_count && -1 != (iret_code = scanf("%d", &val ))) {
                if (1 != iret_code) {
                        fprintf(stderr, "Error: Invalid argument format\n");

                        clear_stdin();
                        continue;
                }

                if (NULL == cll) {
                        cll = create_node(NULL, val);
                        if (NULL == cll) {
                                perror("Error: cannot create head node\n");
                                return -1;
                        }

                        cll->next = cll;
                } else if (NULL == instertAfter(cll, nums, val)) {
                        perror("Error: cannot insert node\n");
                        return -1;
                }

                nums++;
        }

        print(cll);
        free_cll(cll);


        return 0;
}


void clear_stdin()
{
        int c;
        while ('\n' != (c = getchar()) && c != EOF) {
                continue;
        }
}
