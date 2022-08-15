#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#define WAREHOUSE_CAPACITY 10
#define BUYER_SLEEP_TIME_US 1500000
#define DELIVERER_SLEEP_TIME_US 1000000
#define DEFAULT_BUYERS 6
#define DEFAULT_DELIVERERS 5

#define RW_FILE_NAME "warehouse.bin"

enum description{DESC1, DESC2, DESC3, DESC4, DESC5, DESC_COUNT};

struct product_t {
        float price;
        int barcode;
        enum description description;
};

struct node_t {
        struct product_t prod;       
        struct node_t *next;
};

typedef struct sll_t {
        struct node_t *head;
        int capacity;
        int size;
} warehouse;

struct tharg_t {
        int thread_num;
        warehouse *warehouse;
};

struct product_t gen_product();
int randint(int min, int max);
float randfloat(float min, float max);
warehouse create_warehouse(int capacity);
void free_warehouse(warehouse *warehouse);
struct product_t buy_product(warehouse *warehouse, int index);
int deliver_product(warehouse *warehouse, struct product_t product);  // push front
void *buyer(void *args);
void *deliverer(void *args);
void interupt_handler();
int write_warehouse(char *fname, warehouse *warehouse);
int read_warehouse(char *fname, warehouse *warehouse);
int push_back(struct sll_t *sll, struct product_t prod);

pthread_mutex_t warehouse_lock;
sem_t empty_sem;
sem_t full_sem;

warehouse _warehouse;

int main (int argc, char *argv[])
{
        int opt;
        int deliver_cnt = DEFAULT_DELIVERERS;
        int buyer_cnt = DEFAULT_BUYERS;

        while ((opt = getopt(argc, argv, ":b:d:")) != -1) {
                switch (opt) {
                case 'b':
                        buyer_cnt = atoi(optarg);
                        break;
                case 'd':
                        deliver_cnt = atoi(optarg);
                        break;
                }
        }

        struct sigaction interupt_action; 
        interupt_action.sa_handler = interupt_handler;
        sigaction(SIGINT, &interupt_action, NULL);

        if (read_warehouse(RW_FILE_NAME, &_warehouse))
                _warehouse = create_warehouse(WAREHOUSE_CAPACITY);
        else
                printf("Loaded warehouse from file\n");
        

        srand(time(NULL));
        pthread_mutex_init(&warehouse_lock, NULL);
        sem_init(&empty_sem, 0, WAREHOUSE_CAPACITY);
        sem_init(&full_sem, 0, 0);

        pthread_t deliver_threads[deliver_cnt];
        struct tharg_t deliver_thargs[deliver_cnt];
        pthread_t buyer_threads[buyer_cnt];
        struct tharg_t buyer_thargs[buyer_cnt];


        for (int i = 0; i < deliver_cnt; i++) {
                struct tharg_t tharg = {.thread_num = i, .warehouse = &_warehouse};
                deliver_thargs[i] = tharg;
                if (pthread_create(deliver_threads + i, NULL, deliverer, deliver_thargs + i)) {
                        perror("pthread_create");
                        exit(EXIT_FAILURE);
                }
        }

        for (int i = 0; i < buyer_cnt; i++) {
                struct tharg_t tharg = {.thread_num = i, .warehouse = &_warehouse};
                buyer_thargs[i] = tharg;
                if (pthread_create(buyer_threads + i, NULL, buyer, buyer_thargs + i)) {
                        perror("pthread_create");
                        exit(EXIT_FAILURE);
                }
        }
         
        for (int i = 0; i < deliver_cnt; i++) {
                if (pthread_join(deliver_threads[i], NULL)) {
                        perror("pthread_join");
                        exit(EXIT_FAILURE);
                }
        }

        for (int i = 0; i < buyer_cnt; i++) {
                if (pthread_join(buyer_threads[i], NULL)) {
                        perror("pthread_join");
                        exit(EXIT_FAILURE);
                }
        }
        
        pthread_mutex_destroy(&warehouse_lock);
        sem_destroy(&empty_sem);
        sem_destroy(&full_sem);
        free_warehouse(&_warehouse);
        return EXIT_SUCCESS;
}

struct product_t gen_product()
{
        struct product_t new_prod;
        new_prod.price = randfloat(10.00, 1000.00);
        new_prod.barcode = rand();
        new_prod.description = DESC1 + randint(0, DESC_COUNT-1);

        return new_prod;
}

inline int randint(int min, int max)
{
        if (min == max)
                return min;

        return min + (rand() % (1 + max - min));
}

float randfloat(float min, float max)
{
        return min + (rand() / (float) RAND_MAX) * (max - min);
}

warehouse create_warehouse(int capacity)
{
        warehouse warehouse;

        warehouse.capacity = capacity;
        warehouse.head = NULL;
        warehouse.size = 0;

        return warehouse;
}

int deliver_product(warehouse *warehouse, struct product_t product)  // push front
{
        struct node_t *new_node = malloc(sizeof(struct node_t));
        if (NULL == new_node)
                return -1;

        new_node->prod = product;
        new_node->next = warehouse->head;
        warehouse->head = new_node;
        warehouse->size++;

        return 0;
}

int push_back(struct sll_t *sll, struct product_t prod)
{
        struct node_t *new_node = malloc(sizeof(struct node_t));
        if (NULL == new_node)
                return -1;

        new_node->prod = prod;
        new_node->next = NULL;

        if (NULL == sll->head) {
                sll->head = new_node;
        } else {
                struct node_t *iter_node;
                for (iter_node = sll->head; iter_node->next != NULL; iter_node = iter_node->next);
                iter_node->next = new_node;
        }

        sll->size++;

        return 0;
}

struct product_t buy_product(warehouse *warehouse, int index)
{
        struct product_t return_product;

        if (0 == index) {
                struct node_t *next_head = warehouse->head->next;
                return_product = warehouse->head->prod;
                free(warehouse->head);
                warehouse->head = next_head;
                warehouse->size--;
                return return_product;
        }

        struct node_t *prev_node = warehouse->head;
        for (int i = 0; i < index - 1; i++) {
                prev_node = prev_node->next;
        }

        struct node_t *target_node = prev_node->next;
        prev_node->next = target_node->next;
        return_product = target_node->prod;
        free(target_node);
        warehouse->size--;

        return return_product;
}

void free_warehouse(warehouse *warehouse)
{
        do {
                struct node_t *next = warehouse->head->next;
                free(warehouse->head);
                warehouse->head = next;
        } while (NULL != warehouse->head);

}

void *buyer(void *args)
{
        struct tharg_t *tharg = (struct tharg_t *) args;

        int index;
        while(1) {
                usleep(BUYER_SLEEP_TIME_US);

                sem_wait(&full_sem);
                pthread_mutex_lock(&warehouse_lock);
                index = randint(0, tharg->warehouse->size - 1);
                struct product_t bought_prod = buy_product(tharg->warehouse, index);
                pthread_mutex_unlock(&warehouse_lock);
                printf("Buyer %d bought product %d {barcode - %d  price - %f  description - %d}\n", tharg->thread_num, index + 1, bought_prod.barcode, bought_prod.price, bought_prod.description);
                sem_post(&empty_sem);
        }
}

void *deliverer(void *args)
{
        struct tharg_t *tharg = (struct tharg_t *) args;

        int index;
        while(1) {
                usleep(DELIVERER_SLEEP_TIME_US);

                sem_wait(&empty_sem);
                struct product_t deliver_prod = gen_product();
                pthread_mutex_lock(&warehouse_lock);
                deliver_product(tharg->warehouse, deliver_prod);
                index = tharg->warehouse->size;
                pthread_mutex_unlock(&warehouse_lock);
                printf("Deliverer %d delivered product %d {barcode - %d  price - %f  description %d}\n", tharg->thread_num, index, deliver_prod.barcode, deliver_prod.price, deliver_prod.description);
                sem_post(&full_sem);
        }
}

void interupt_handler()
{
        if (write_warehouse(RW_FILE_NAME, &_warehouse)) {
                fprintf(stderr, "cannot write warehouse to file\n");
                exit(EXIT_FAILURE);
        }

        printf("\nWrote warehouse to file\n");
        exit(EXIT_SUCCESS);
}

int write_warehouse(char *fname, warehouse *warehouse)
{
        FILE *fp = fopen(fname, "wb");
        if (NULL == fp)
                return -1;

        for(struct node_t *iter_node = warehouse->head; iter_node != NULL; iter_node = iter_node->next) {
                if (fwrite(&iter_node->prod, sizeof(iter_node->prod), 1, fp) != 1)
                        return -1;
        }

        fclose(fp);
        return 0;
}

int read_warehouse(char *fname, warehouse *warehouse)
{
        FILE *fp = fopen(fname, "rb");
        if (NULL == fp)
                return -1;

        struct product_t next_prod;
        while (fread(&next_prod, sizeof(next_prod), 1, fp) == 1) {
                push_back(warehouse, next_prod);
        }

        if (!feof(fp))
                return -1;

        return 0;
}
