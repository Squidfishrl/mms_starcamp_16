#include <stdio.h>
#include <stdlib.h>

#define RW_SIZE 100

int main (int argc, char *argv[])
{
        char buff[RW_SIZE];

        while (NULL != *(++argv)) {
                FILE *fp = fopen(*argv, "r");
                int bytes;

                while ((bytes = fread(buff, sizeof(char), RW_SIZE, fp)) > 0) {
                        if (fwrite(buff, sizeof(char), bytes, stdout) != bytes) {
                                perror("fwrite");
                                return EXIT_FAILURE;
                        }
                }

                if (!feof(fp)) {
                        perror("fread");
                        return EXIT_FAILURE;
                }


                fclose(fp);
        }
}
