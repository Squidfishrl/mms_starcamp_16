#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

struct sll_t {
        struct node_t *head;
};

struct node_t {
        struct Book data;
        struct node_t *next;
};

int sorted_insert(struct sll_t *sll, struct Book *data);
void free_sll(struct sll_t *sll);

int main (int argc, char *argv[])
{
        if (argc != 3) {
                fprintf(stderr, "Invalid arguments. Expected './program input output'\n");
                exit(EXIT_FAILURE);
        }

        FILE *f_in = fopen(argv[1], "rb");

        struct Book book;

        struct sll_t sll;
        sll.head = NULL;

        while(fread(&book, sizeof(struct Book), 1, f_in) == 1) {
                if (sorted_insert(&sll, &book)) {
                        perror("sorted_insert");
                        exit(EXIT_FAILURE);
                }
        }

        if (!feof(f_in)) {
                perror("fread");
                exit(EXIT_FAILURE);
        }

        fclose(f_in);

#ifdef VERBOSE 
        for (struct node_t *iter_node = sll.head; iter_node != NULL; iter_node = iter_node->next) {
                printf("%s\n", iter_node->data.title);
        }
#endif // !VERBOSE

        FILE *f_out = fopen(argv[2], "wb");
        for (struct node_t *iter_node = sll.head; iter_node != NULL; iter_node = iter_node->next) {
                if (fwrite(&iter_node->data, sizeof(iter_node->data), 1, f_out) != 1) {
                        perror("fwrite");
                        exit(EXIT_FAILURE);
                }
        }

        fclose(f_out);


        free_sll(&sll);
        return 0;
}

struct node_t *create_node(struct Book data, struct node_t *next)
{
        struct node_t *new_node = malloc(sizeof(struct node_t));
        if (NULL == new_node)
                return NULL;

        new_node->data = data;
        new_node->next = next;
        return new_node;
}

int sorted_insert(struct sll_t *sll, struct Book *data)
{
        if (NULL == sll->head) {
                sll->head = create_node(*data, NULL);
                return !(NULL != sll->head);
        }

        struct node_t *new_node;

        for (struct node_t *prev_node = sll->head, *iter_node = sll->head; iter_node != NULL; iter_node = iter_node->next) {
                int comparison = strcmp(iter_node->data.title, data->title);

                if (comparison >= 0) {
                        new_node = create_node(*data, iter_node);
                        if (NULL == new_node)
                                return -1;

                        if (prev_node == iter_node)
                                sll->head = new_node;
                        else
                                prev_node->next = new_node;

                        return 0;
                } else {
                        if (NULL == iter_node->next) {
                                new_node = create_node(*data, NULL);
                                if (NULL == new_node)
                                        return -1;

                                iter_node->next = new_node;
                                return 0;
                        }
                }

                prev_node = iter_node;
        }

        return -1;
}

void free_sll(struct sll_t *sll)
{
        do {
                struct node_t *next = sll->head->next;
                free(sll->head);
                sll->head = next;
        } while(sll->head != NULL);
}
