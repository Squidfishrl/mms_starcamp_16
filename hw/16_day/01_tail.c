#include <stdio.h>
#include <stdlib.h>

#define RW_SIZE 100
#define LINES 10

int main (int argc, char *argv[])
{
        char buff[RW_SIZE];

        while (NULL != *(++argv)) {
                FILE *fp = fopen(*argv, "r");
                int line_count = 0;
                int total_bytes = 0;
                int bytes;

                if (fseek(fp, -RW_SIZE, SEEK_END)) {
                        perror("fseek");
                        return EXIT_FAILURE;
                }

                while ((bytes = fread(buff, sizeof(char), RW_SIZE, fp)) > 0) {

                        for (int i = 0; i < bytes; i++) {
                                line_count += (buff[i] == '\n');

                                if (LINES == line_count) {
                                        bytes = i + 1;
                                        break;
                                }
                        }

                        total_bytes += bytes;
                        if (fseek(fp, -bytes, SEEK_CUR)) {
                                perror("fseek");
                                return EXIT_FAILURE;
                        }

                        if (LINES == line_count)
                                break;
                }

                if (ferror(fp)) {
                        perror("fread");
                        return EXIT_FAILURE;
                }

                if (fseek(fp, -total_bytes, SEEK_END)){
                        perror("fseek");
                        return EXIT_FAILURE;

                }

                if (fwrite(buff, sizeof(char), total_bytes, stdout) != total_bytes) {
                        perror("fwrite");
                        return EXIT_FAILURE;
                }

                fclose(fp);
        }
}
