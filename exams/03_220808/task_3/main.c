#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define PRODUCT_AMOUNT 40 
#define PRICE_CMP_THRESHOLD 0.01
#define WRITE_FNAME "write_file"

struct Product {
        double old_price;
        double new_price;
        unsigned int id;
        char product_type;
        char product_name[35];
};

struct Product rand_product(char **rand_names, size_t size);
double rand_dbl(double min, double max, int precision);
int rand_int(int min, int max);
void print_product(struct Product product);
int product_cmp(const void *, const void *);
int write_products(char *fname, struct Product *products, size_t products_amount);
int read_products(char *fname, struct Product *products, size_t products_amount);

int main (int argc, char *argv[])
{
        srand(time(NULL));
        struct Product products[PRODUCT_AMOUNT];

        char *rand_names[] = {
                "01_Name",
                "02_Name",
                "03_Name",
                "04_Name",
                "05_Name",
                "06_Name",
        };

        for (int i = 0; i < PRODUCT_AMOUNT; i++) {
                products[i] = rand_product(rand_names, 6);
                print_product(products[i]);
        }

        qsort(products, PRODUCT_AMOUNT, sizeof(*products), product_cmp);

        printf("\n\nSORTED: \n\n");
        for (int i = 0; i < PRODUCT_AMOUNT; i++) {
                print_product(products[i]);
        }

        if (write_products(WRITE_FNAME, products, PRODUCT_AMOUNT)) {
                fprintf(stderr, "Erorr: cannot write to file");
                return -1;
        }

        struct Product read_arr[PRODUCT_AMOUNT];
        if (read_products(WRITE_FNAME, read_arr, PRODUCT_AMOUNT)) {
                fprintf(stderr, "Error: cannot read from file");
                return -1;
        }

        printf("\n\nFROM FILE: \n\n");
        for (int i = 0; i < PRODUCT_AMOUNT; i++) {
                print_product(read_arr[i]);
        }



        return 0;
}

int read_products(char *fname, struct Product *products, size_t products_amount)
{
        FILE *f_ptr = fopen(fname, "r");
        if (NULL == f_ptr)
                return -1;

        if (PRODUCT_AMOUNT != fread(products, sizeof(struct Product), products_amount, f_ptr))
                return -1;

        fclose(f_ptr);
        return 0;
}

int write_products(char *fname, struct Product *products, size_t products_amount)
{
        FILE *f_ptr = fopen(fname, "w");
        if (NULL == f_ptr)
                return -1;

        if (PRODUCT_AMOUNT != fwrite(products, sizeof(struct Product), products_amount, f_ptr))
                return -1;

        fclose(f_ptr);
        return 0;
}

int product_cmp(const void *product1, const void *product2)
{
        struct Product p1 = *(struct Product *) product1;
        struct Product p2 = *(struct Product *) product2;

        double p1_price_rise = p1.new_price - p1.old_price;
        double p2_price_rise = p2.new_price - p2.old_price;

        if (fabs(p1_price_rise - p2_price_rise) >= PRICE_CMP_THRESHOLD)
                return p1_price_rise - p2_price_rise;

        if (p1.product_type != p2.product_type)
                return p1.product_type - p2.product_type;

        int name_comparison = strcmp(p1.product_name, p2.product_name);
        if (name_comparison)
                return name_comparison;

        return -(p1.id - p2.id);
}

void print_product(struct Product product)
{
        printf("\n%s(%c) - %d\n", product.product_name, product.product_type, product.id);
        printf("----------------\n");
        printf("old price: %.2lf\n", product.old_price);
        printf("new price: %.2lf\n", product.new_price);
}

struct Product rand_product(char **rand_names, size_t size)
{
        static int id_counter = 0;

        struct Product new_product;
        new_product.old_price = rand_dbl(4.99, 100.45, 2);
        new_product.new_price = rand_dbl(4.99, 100.45, 2);

        new_product.product_type = 'A' + rand_int(0, 4);
        strncpy(new_product.product_name, rand_names[rand_int(0, size)], 35);
        new_product.id = id_counter++;

        return new_product;
}
double rand_dbl(double min, double max, int precision)
{
        int precision_magnitude = pow(10, precision);
        int imax = max * precision_magnitude;
        int imin = min * precision_magnitude;

        return ((rand() % (imax - imin)) + imin) / (double) precision_magnitude;
}

inline int rand_int(int min, int max)
{
        return (rand() % (max - min)) + min;
}
