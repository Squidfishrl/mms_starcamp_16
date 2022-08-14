#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <unistd.h>

#include "ffprint.h"


int ffprint(int fd, char *format, ...)
{
        struct queue_t str_q = create_q();
        int formats = 0;

        va_list ap;
        va_start(ap, format);

        char *temp_str;
        char *old_enq_pos = format;
        char *c;
        for (c = format; *c != '\0'; c++) {
                if (*c == '%') {
                        if (c != old_enq_pos) {
                                temp_str = malloc(sizeof(char) * (c - old_enq_pos));
                                if (NULL == temp_str)
                                        return -1;

                                _strncpy(temp_str, old_enq_pos, sizeof(char) * (c - old_enq_pos));
                                if (enqueue(&str_q, temp_str, c - old_enq_pos))
                                        return -1;
                        }

                        c++;

                        int arg_len;
                        switch (*c) {
                        case 'd':;
                                int inum = va_arg(ap, int);
                                arg_len = count_int_digits(inum);
                                temp_str = malloc(sizeof(char) * arg_len);
                                if (NULL == temp_str)
                                        return -1;

                                _int_to_str(temp_str, inum);
                                if (enqueue(&str_q, temp_str, arg_len))
                                        return -1;
                                break;
                        case 'f':;
                                float fnum = (float) va_arg(ap, double);
                                arg_len = count_int_digits((int) fnum);
                                temp_str = malloc(sizeof(char) * arg_len + 1 + FLOAT_PRECISION);
                                if (NULL == temp_str)
                                        return -1;

                                _float_to_str(temp_str, fnum, arg_len);
                                if (enqueue(&str_q, temp_str, arg_len + 1 + FLOAT_PRECISION))
                                        return -1;
                                break;
                        case 'c':
                                temp_str = malloc(sizeof(char));
                                if (NULL == temp_str)
                                        return -1;

                                *temp_str = (char) va_arg(ap, int);
                                if (enqueue(&str_q, temp_str, 1))
                                        return -1;
                                break;
                        case 's':;
                                char *arg_str = va_arg(ap, char *);
                                arg_len = _strlen(arg_str);
                                temp_str = malloc(sizeof(char) * arg_len);
                                if (NULL == temp_str)
                                        return -1;

                                _strncpy(temp_str, arg_str, arg_len);
                                if (enqueue(&str_q, temp_str, arg_len))
                                        return -1;
                                break;
                                
                        default:
                                temp_str = malloc(sizeof(char) * 2);
                                if (NULL == temp_str)
                                        return -1;

                                *temp_str = '%';
                                *(temp_str + 1) = *c;
                                if (enqueue(&str_q, temp_str, 2))
                                        return -1;
                                break;
                        }

                        old_enq_pos = 1 + c;
                }
        }
        va_end(ap);

        temp_str = malloc(sizeof(char) * (c - old_enq_pos));
        if (NULL == temp_str)
                return -1;

        _strncpy(temp_str, old_enq_pos, sizeof(char) * (c - old_enq_pos));
        enqueue(&str_q, temp_str, c - old_enq_pos);

        char final_buf[str_q.str_size];
        write_to_buf(final_buf, &str_q);

       
        if (write(fd, final_buf, str_q.str_size) != str_q.str_size)
                return -1;


        free_queue(&str_q);
        return 0;
}

int enqueue(struct queue_t *q, char *str, int size)
{
        if (NULL == q->head) {
                q->head = q->tail = create_qnode(str, size, NULL);
                if (NULL == q->head)
                        return -1;

                q->str_size += size;
                return 0;
        }

        q->tail->next = create_qnode(str, size, NULL);
        if (NULL == q->tail->next)
                return -1;

        q->tail = q->tail->next;

        if (NULL == q->head->next) {
                q->head->next = q->tail;
        }

        q->str_size += size;
        return 0;
}

char *dequeue(struct queue_t *q)
{
        if (NULL == q->head)
                return NULL;

        char *data = q->head->str;
        q->str_size -= q->head->str_size;
        struct qnode_t *new_head = q->head->next;
        free(q->head);
        q->head = new_head;

        return data;
}

struct qnode_t *create_qnode(char *str, int size, struct qnode_t *next)
{
        struct qnode_t *new_qnode = malloc(sizeof(struct qnode_t));
        if (NULL == new_qnode)
                return NULL;

        new_qnode->str = str;
        new_qnode->next = next;
        new_qnode->str_size = size;

        return new_qnode;
}

void free_queue(struct queue_t *q)
{
        char *str;
        while((str = dequeue(q)) != NULL) {
                free(str);
        }

        q->head = q->tail = NULL;
}

int count_int_digits(int num)
{
        if (num < 0) 
                num *= -1;

        int counter = 1;
        for(; num > 0; num /= 10, counter++);
        return counter;
}

void _int_to_str(char *dest, int src)
{
        if (src == 0) {
                *dest = '0';
                return;
        }

        char *start = dest;

        src = abs(src);
        while(src > 0) {
                *dest = (src % 10) + '0';
                dest++;
                src /= 10;
        }

        while (start < dest) {
                char temp = *dest;
                *dest = *start;
                *start = temp;

                start++;
                dest--;
        }
}

void _float_to_str(char *dest, float src, int initial_digits)
{
        _int_to_str(dest, (int) src);
        dest += initial_digits;
        *dest = '.';
        src -= (int) src;
        src *= pow(10, FLOAT_PRECISION);
        _int_to_str(dest+1, (int) src);
}

struct queue_t create_q()
{
        struct queue_t new_q;

        new_q.head = NULL;
        new_q.tail = NULL;

        return new_q;
}

void write_to_buf(char *dest, struct queue_t *q)
{
        for (struct qnode_t *iter_node = q->head; iter_node != NULL; iter_node = iter_node->next) {
                for (int i = 0; i < iter_node->str_size; i++) {  // for unknown reason strncpy doesn't work here
                        *dest++ = *(iter_node->str+i);
                }
        }
}

void _strncpy(char *dest, const char *src, int bytes)
{
        for (int i = 0; i < bytes; *dest++ = *src++, i++);
}

int _strlen(char *str)
{
        int len = 0;
        for (; *(str + len) != '\0'; len++);
        return len;
}
