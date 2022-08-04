#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int fd_in = open(argv[1], O_RDONLY);
    if (-1 == fd_in) {
        perror("Cannot open file");
        return -1;
    }

    int fd_out = open(argv[2], O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR);
    if (-1 == fd_out) {
        perror("Cannot open file");
        return -1;
    }

    char buf;
    int read_res;
    while (0 != (read_res = read(fd_in, &buf, 1))) {
        
        if (-1 == read_res) {
            perror("Could not read from file");
            return -1;
        }

        if (0 == write(fd_out, &buf, 1)) {
            perror("Could not read from file");
            return -1;
        }
    }

    close(fd_in);
    close(fd_out);

    return 0;
}
