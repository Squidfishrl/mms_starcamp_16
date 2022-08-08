#ifndef __CLL_H__
#define __CLL_H__

struct Node {
        int data;
        struct Node *next;
};

void print(struct Node *cll);
struct Node *create_node(struct Node *next, int data);
struct Node *instertAfter(struct Node *cll, int skipCount, int newElem);
void free_cll(struct Node *cll);

#endif // !__CLL_H__
