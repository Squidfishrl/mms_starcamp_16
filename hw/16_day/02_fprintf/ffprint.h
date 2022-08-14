#ifndef __FFPRINT_H__
#define __FFPRINT_H__

#define FLOAT_PRECISION 5

struct queue_t {
        struct qnode_t *head;
        struct qnode_t *tail;
        int str_size;
};

struct qnode_t {
        char *str;
        int str_size;
        struct qnode_t *next;
};

struct queue_t create_q();
struct qnode_t *create_qnode(char *str, int size, struct qnode_t *next);
int enqueue(struct queue_t *q, char *str, int size);
char *dequeue(struct queue_t *q);
void free_queue(struct queue_t *q);
void write_to_buf(char *dest, struct queue_t *q);

int ffprint(int fd, char *format, ...);
int count_int_digits(int num);
void _int_to_str(char *dest, int src);
void _float_to_str(char *dest, float src, int initial_digits);
void _strncpy(char *dest, const char *src, int bytes);  // strncpy from <string.h> doesn't work when struct qnode_t holds a converted format for some reason???
int _strlen(char *str);

#endif // !__FFPRINT_H__
