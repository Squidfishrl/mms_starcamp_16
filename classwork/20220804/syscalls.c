#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int fd = open("test_binary", O_WRONLY | O_TRUNC);
    if (-1 == fd)
        perror("couldn't open file");

    int buf[] = {1, 2, 3};
    int sys_num = sizeof(buf);
    if (write(fd, buf, sys_num) != sys_num)
        write(2, "Could not write to file\n", 22);

    close(fd);

    return 0;
}
