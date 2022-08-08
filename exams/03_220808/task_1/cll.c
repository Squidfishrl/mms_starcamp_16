#include <stdio.h>
#include <stdlib.h>

#include "cll.h"

void print(struct Node *cll)
{
        if (NULL == cll) {
                putchar('\n');
                return;
        }

        struct Node *iter_node = cll;

        do {
                printf("%d ", iter_node->data);
                iter_node = iter_node->next;
        } while (iter_node != cll);

        putchar('\n');
}

struct Node *create_node(struct Node *next, int data)
{
        struct Node *new_node = malloc(sizeof(struct Node));
        if (NULL == new_node)
                return NULL;

        new_node->data = data;
        new_node->next = next;

        return new_node;
}

struct Node *instertAfter(struct Node *cll, int skipCount, int newElem)
{
        if (skipCount < 0 || skipCount > 1000000)
                return NULL;

        if (NULL == cll)
                return NULL;

        struct Node *prev = cll;

        // OPT: keep track of list size and use the modulus operator if skipCount exceeds the size
        for (int i = 0; i < skipCount; i++) {
                prev = prev->next; 
        }

        struct Node *new_node = create_node(prev->next, newElem);
        if (NULL == new_node)
                return NULL;

        prev->next = new_node;

        return new_node;
}

void free_cll(struct Node *cll)
{
        if (NULL == cll)
                return;

        struct Node *iter_node = cll;
        do {
                struct Node *prev = iter_node;
                iter_node = iter_node->next;
                free(prev);
        } while (iter_node != cll);

        cll = NULL;
}
