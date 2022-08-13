#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "book.h"

#define COUNT 10

int randint(int min, int max);
float randfloat(float min, float max);
struct Book gen_book();

int main (int argc, char *argv[])
{
        if (argc != 2) {
                fprintf(stderr, "Invalid arguments\n");
                exit(EXIT_FAILURE);
        }

        srand(time(NULL));

        struct Book books[COUNT];

        for (int i = 0; i < COUNT; i++) {
                books[i] = gen_book();
        }

        FILE *fp = fopen(argv[1], "wb");
        if (0 == fp) {
                perror("fopen");
                exit(EXIT_FAILURE);
        }

        if (fwrite(books, sizeof(books[0]), COUNT, fp) != COUNT) {
                perror("fwrite");
                exit(EXIT_FAILURE);
        }

        fclose(fp);

        return 0;
}

struct Book gen_book()
{
        struct Book new_book;
        
        int title_chars = randint(10, 20);
        int to_cap = 'A' - 'a';
        for (int i = 0; i < title_chars; i++) {
                int is_cap = randint(0, 1);
                new_book.title[i] = randint('a', 'z') + (is_cap ? to_cap : 0);
        }

        int author_chars = randint(10, 20);
        for (int i = 0; i < author_chars; i++) {
                int is_cap = randint(0, 1);
                new_book.author[i] = randint('a', 'z') + (is_cap ? to_cap : 0);
        }

        new_book.pages = randint(5, 2000);
        new_book.price = randfloat(1.00, 1000.00);

        return new_book;
}

inline int randint(int min, int max)
{
        return min + (rand() % (1 + max - min));
}

float randfloat(float min, float max)
{
        return min + ((rand() / (float)RAND_MAX) * (max - min));
}
