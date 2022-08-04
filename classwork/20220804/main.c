#include "sll.h"
#include <stdlib.h>

int main (int argc, char *argv[])
{
    struct list_t sll = {.head=NULL, .size=0};
    push_back(&sll, 2);
    push_back(&sll, 3);
    push_back(&sll, 4);
    push_front(&sll, 1);
    push_front(&sll, 0);
    print_ll(&sll); // 0 1 2 3 4
    pop_front(&sll);
    pop_front(&sll);
    pop_back(&sll);
    print_ll(&sll); // 2 3

    free_ll(&sll);
    return 0;

}
