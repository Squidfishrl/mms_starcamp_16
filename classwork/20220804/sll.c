#include <stdlib.h>
#include <stdio.h>

#include "sll.h"

int push_front(struct list_t *sll, long value)
{
        struct node_t *new_node = malloc(sizeof(struct node_t));
        if (NULL == new_node)
                return -1;

        new_node->value = value;
        new_node->next = sll->head;
        sll->head = new_node;
        sll->size++;

        return 0;
}

int push_back(struct list_t *sll, long value)
{

        struct node_t *new_node = malloc(sizeof(struct node_t));
        if (NULL == new_node)
                return -1;

        new_node->value = value;
        new_node->next = NULL;

        struct node_t *last_node;
        for (last_node = sll->head; NULL != last_node && NULL != last_node->next; last_node = last_node->next);

        if (NULL == last_node)
                sll->head = new_node;
        else
                last_node->next = new_node;

        sll->size++;

        return 0;
}

void pop_back(struct list_t *sll)
{
        struct node_t *last_node, *second_to_last_node;

        second_to_last_node = sll->head;

        if (NULL == second_to_last_node)
                return;

        last_node = second_to_last_node->next;

        while (NULL != last_node && NULL != last_node->next ) {
                second_to_last_node = last_node;
                last_node = last_node->next;
        }

        second_to_last_node->next = NULL;
        free(last_node);

        sll->size--;
}

void pop_front(struct list_t *sll)
{
        struct node_t *old_head = sll->head;

        if (NULL == old_head)
                return;

        sll->head = old_head->next;
        free(old_head);

        sll->size--;
}

void print_ll(const struct list_t *sll)
{
        for (struct node_t *inode = sll->head; NULL != inode; inode = inode->next) {
                printf("%ld ", inode->value);
        }

        putchar('\n');
}

void reverse(struct list_t *sll)
{
        struct node_t *next = NULL;
        struct node_t *current = sll->head;
        struct node_t *previous = NULL;

        while (NULL != current) {
                next = current->next;
                current->next = previous;
                previous = current;
                current = next;
        }

        sll->head = previous;
}

void free_ll(struct list_t *sll)
{
        struct node_t *inode = sll->head;

        while(NULL != inode) {
                struct node_t *next_node = inode->next;
                free(inode);
                inode = next_node;
        }

        sll->size = 0;
        sll->head = NULL;
}
