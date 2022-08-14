#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <stdint.h>

union bool_opts {
        uint8_t mask;

        struct {
                uint8_t file:1;
                uint8_t dir:1;
                uint8_t secret:1;
        };
};

int ls(char *path, union bool_opts opts);

int main (int argc, char *argv[])
{
        int opt;
        union bool_opts bool_opts;
        bool_opts.file = 1;
        bool_opts.dir = 1;

        while ((opt = getopt(argc, argv, ":fdaA")) != -1) {
                switch (opt) {
                case 'f':
                        bool_opts.file = 1;
                        break;
                case 'd':
                        bool_opts.dir = 1;
                        break;
                case 'a':
                        bool_opts.secret = 1;
                        break;
                case 'A':
                        bool_opts.mask = UINT8_MAX;
                        break;
                case '?':
                        printf("Unknown option: %c\n", optopt);
                }
        }

        uint8_t has_path = 0;
        for (; optind < argc; optind++) {
                has_path = 1;
                if (ls(argv[optind], bool_opts)) {
                        fprintf(stderr, "ls error");
                        return -1;
                }
        }

        if (0 == has_path) {
                if (ls(".", bool_opts)) {
                        fprintf(stderr, "ls error");
                        return -1;
                }

        }
}

int ls(char *path, union bool_opts opts)
{
        DIR *dir; 
        struct dirent *ent;

        if ((dir = opendir(path)) == NULL) {
                perror("opendir");
                return -1;
        }

        while ((ent = readdir(dir)) != NULL) {
                if (0 == opts.file && DT_REG == ent->d_type)
                        continue;

                if (0 == opts.dir && DT_DIR == ent->d_type)
                        continue;

                if (0 == opts.secret && ent->d_name[0] == '.' && ent->d_name[1] != '.' && ent->d_name[1] != '\n')
                        continue;
                
                printf("%s\n", ent->d_name);
        }

        putchar('\n');
        closedir(dir);
        return 0;
}
