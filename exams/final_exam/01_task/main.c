#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

#ifndef LAPTOPS_COUNT
#define LAPTOPS_COUNT 10
#endif // !LAPTOPS_COUNT
#define BRAND_LEN 100
#define MIN_BRAND_LETTERS 8
#define MAX_BRAND_LETTERS 12

typedef struct Laptop {
        unsigned long long serial_number;
        char brand[BRAND_LEN];
        double weight;
        double price;
} Laptop;

struct Laptop gen_laptop();
int randint(int min, int max);
double randdouble(double min, double max);
double totalLaptopWeight(Laptop *laptops);
double minPriceItem(Laptop *laptops);
void print_laptops(Laptop *laptops);


int main (int argc, char *argv[])
{
        srand(time(NULL));
        struct Laptop *laptops = malloc(sizeof(laptops[0]) * (LAPTOPS_COUNT+1));
        for (int i = 0; i < LAPTOPS_COUNT; i++) {
                laptops[i] = gen_laptop();
        }

        print_laptops(laptops);

        free(laptops);
        return 0;
}

struct Laptop gen_laptop()
{
        static int serial_number_cnt = 0;

        struct Laptop new_laptop;
        new_laptop.serial_number = serial_number_cnt++;

        // starts with a capital letter and has 8-12 random letters separated by whitespace
        int letter_cnt = randint(MIN_BRAND_LETTERS, MAX_BRAND_LETTERS);
        for (int i = 0; i < letter_cnt * 2 - 1; i++) {
                new_laptop.brand[i] = randint('a', 'z');
                new_laptop.brand[++i] = ' ';
        }

        // capitalize first letter
        new_laptop.brand[0] += 'A' - 'a';
        new_laptop.brand[letter_cnt * 2 - 1] = '\0';

        new_laptop.weight = randdouble(0.025, 10.00);
        new_laptop.price = randdouble(10.00, 5000.00);

        return new_laptop;
}

double randdouble(double min, double max)
{
        return min + (rand() / (double) RAND_MAX) * (1 + max - min);
}

inline int randint(int min, int max)
{
        return min + (rand() % (1 + max - min));
}

double totalLaptopWeight(Laptop *laptops)
{
        if (NULL == laptops)
                return -1;

        double weight_sum = 0;

        for (int i = 0; i < LAPTOPS_COUNT; i++) {
                weight_sum += laptops[i].weight;
        }

        return weight_sum;
}

double minPriceItem(Laptop *laptops)
{
        if (NULL == laptops)
                return -1;

        double min_price = DBL_MAX;
        for (int i = 0; i < LAPTOPS_COUNT; i++) {
                if (laptops[i].price < min_price)
                        min_price = laptops[i].price;
        }

        return min_price;
}

void print_laptops(Laptop *laptops)
{
        if (NULL == laptops)
                return;

        for (int i = 0; i < LAPTOPS_COUNT; i++) {
                printf(
                        "--------------------------------------------------\n"  \
                        "Serial number  - %lld\n"                               \
                        "Brand          - %s\n"                                 \
                        "Weight         - %.3lf\n"                              \
                        "Price          - %.2lf\n",
                        laptops[i].serial_number, laptops[i].brand, laptops[i].weight, laptops[i].price
                );
        }

        printf("\ntotal weight - %lf\ncheapest laptop - %lf\n", totalLaptopWeight(laptops), minPriceItem(laptops));
}
