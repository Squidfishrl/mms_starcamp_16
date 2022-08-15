#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef THREAD_COUNT
#define THREAD_COUNT 5
#endif // !THREAD_COUNT

#define MIN_VAL -200.00
#define MAX_VAL 200.00

struct tharg_t {
        int thread_num;
        FILE *fp_write;
        struct sll_t *sll;
};

struct node_t {
        double *vector;       
        struct node_t *next;
};

struct sll_t {
        struct node_t *head;
        int vector_dimension;
};

int enqueue(struct sll_t *sll, double *vector);
double *dequeue(struct sll_t *sll);
void free_sll(struct sll_t *sll);

void *parse_vector(void *args);

double total_sum = 0;
sem_t queue_sem;
pthread_mutex_t sum_lock;

int main (int argc, char *argv[])
{
        int vector_cnt;
        int vector_dimension;

        int opt;
        while ((opt = getopt(argc, argv, "N:M:")) != 1) {
                switch (opt) {
                case 'N':
                        vector_cnt = atoi(optarg);
                        break;
                case 'M':
                        vector_dimension = atoi(optarg);
                        break;
                }
        }

        if (optind >= argc) {
                fprintf(stderr, "expected argument after options\n");
                return EXIT_FAILURE;
        }

        char *out_fname = argv[optind];

        sem_init(&queue_sem, 0, 0);
        pthread_mutex_init(&sum_lock, NULL);

        double *vector;

        pthread_t threads[THREAD_COUNT];
        struct tharg_t thargs[THREAD_COUNT];

        struct sll_t sll;
        sll.vector_dimension = vector_dimension;
        sll.head = NULL;

        
        FILE *fp_w = fopen(out_fname, "w");
        if (NULL == fp_w) {
                perror("fopen");
                return EXIT_FAILURE;
        }

        for (int i = 0; i < THREAD_COUNT; i++) {
                struct tharg_t tharg = {.thread_num = i, .sll = &sll, .fp_write = fp_w};
                thargs[i] = tharg;
                if (pthread_create(threads+i, NULL, parse_vector, &thargs[i])) {
                        perror("pthread_create");
                        return EXIT_FAILURE;
                }
        }

        for (int i = 0; i < vector_cnt; i++) {
                // push back (Use dynamic memory for vector)
                vector = calloc(sizeof(int) * vector_dimension, 0);
                if (NULL == vector) {
                        perror("malloc");
                        return EXIT_FAILURE;
                }

                for (int j = 0; j < vector_dimension; j++) {
                        if (fscanf(stdin, "%lf ", vector+j) != 1) {
                                perror("fscanf");
                                break;
                        }

                        if (vector[j] < MIN_VAL || vector[j] > MAX_VAL) {
                                fprintf(stderr, "value exceeds limits\n");
                                break;
                        }
                }

                enqueue(&sll, vector);
                
                sem_post(&queue_sem);
        }

        for (int i = 0; i < THREAD_COUNT; i++) {
                if (pthread_join(threads[i], NULL)) {
                        perror("pthread_join");
                        return EXIT_FAILURE;
                }
        }

        fclose(fp_w);
        pthread_mutex_destroy(&sum_lock);
        sem_destroy(&queue_sem);
        return EXIT_SUCCESS;
}

void *parse_vector(void *args)
{
        struct tharg_t *tharg = (struct tharg_t *)tharg;
        struct sll_t *sll = tharg->sll;
        FILE *fp = tharg->fp_write;
        int thread_num = tharg->thread_num;

        double result;

        while (1) {
                sem_wait(&queue_sem);

                result = 0;
                double *vector = dequeue(sll);

                for (int i = 0; i < sll->vector_dimension; i++) {
                        result += vector[i] * vector[i];
                }

                result = sqrt(result);
                printf("Thread %d - %lf", thread_num, result);

                free(vector);
                
                pthread_mutex_lock(&sum_lock);
                total_sum += result;
                // TODO: also add the vector elements here
                fprintf(fp, "%lf\n", result);
                pthread_mutex_unlock(&sum_lock);
        }
}

int enqueue(struct sll_t *sll, double *vector)
{
        struct node_t *new_node = malloc(sizeof(struct node_t));
        if (NULL == new_node)
                return EXIT_FAILURE;

        new_node->vector = vector;
        new_node->next = NULL;

        if (NULL == sll->head) {
                sll->head = new_node;
        } else {
                struct node_t *iter_node;
                for (iter_node = sll->head; iter_node->next != NULL; iter_node = iter_node->next);
                iter_node->next = new_node;
        }


        return EXIT_SUCCESS;
}

void free_sll(struct sll_t *sll)
{
        do {
                struct node_t *next = sll->head->next;
                free(sll->head->vector);
                free(sll->head);
                sll->head = next;
        } while (NULL != sll->head);

}

double *dequeue(struct sll_t *sll)
{
        if (NULL == sll->head)
                return NULL;

        double *vector = sll->head->vector;
        
        struct node_t *next_head = sll->head->next;
        free(sll->head);
        sll->head = next_head;

        return vector;
}
