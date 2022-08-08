#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

// OPT: changing block size to something other than 1 (doesn't work yet) 
#define BLOCK_SIZE 1
#define BIN 'B'
#define HEX 'H'

void xxd_print(char *buf, char mode);
void char_to_bin(char *buf, char c);

int main (int argc, char *argv[])
{
        // argv[1] - filename
        // argv[2] - print_mode 

        if (3 != argc) {
                fprintf(stderr, "Error: invalid argument amount\n");
                return -1;
        }

        if ('-' != argv[2][0] || (BIN != argv[2][1] && HEX != argv[2][1])) {
                fprintf(stderr, "Error: invalid argument <print_mode>\n");
                return -1;
        }

        FILE *f_ptr = fopen(argv[1], "r");
        if (NULL == f_ptr) {
                perror("fopen");
                return -1;
        }

        char buf[BLOCK_SIZE];

        while (BLOCK_SIZE == fread(buf, sizeof(char), BLOCK_SIZE, f_ptr) && !feof(f_ptr)) {
                xxd_print(buf, argv[2][1]);
        }

        putchar('\n');

        fclose(f_ptr);

    return 0;
}

// OPT: print in block size as well
void xxd_print(char *buf, char mode)
{
        if (HEX == mode) {
                for (int i = 0; i < BLOCK_SIZE; i++) {
                        printf("%x ", buf[i]);
                }
        } else if (BIN == mode) {
                char bin_buf[CHAR_BIT];

                for (int i = 0; i < BLOCK_SIZE; i++) {
                        char_to_bin(bin_buf, buf[i]);
                        printf("%s ", bin_buf);
                }

        }
}

void char_to_bin(char *buf, char c)
{
        for (int i = 0; i < CHAR_BIT; i++) {
                buf[CHAR_BIT - i - 1] = (c & (1 << i) ? '1' : '0');
        }
}
