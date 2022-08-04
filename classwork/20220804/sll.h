#ifndef __SLL_H__
#define __SLL_H__

struct node_t {
        struct node_t *next;
        long value;
};

struct list_t {
        struct node_t *head;
        unsigned int size;
};

int push_front(struct list_t *sll, long value);
int push_back(struct list_t *sll, long value);
void pop_back(struct list_t *sll);
void pop_front(struct list_t *sll);
void print_ll(const struct list_t *sll);
void reverse(struct list_t *sll);
void free_ll(struct list_t *sll);

#endif // !__SLL_H__
