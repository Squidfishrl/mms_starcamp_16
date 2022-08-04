#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_t{
    double grade;
    char name[7];
    unsigned char age;
    unsigned int courses_taken;
};

int main (int argc, char *argv[])
{
    FILE *f_ptr = fopen("test.txt", "wb");
    if(!f_ptr) {
        perror("Could not open file\n");
        exit(-1);
    }

    struct student_t arr[5] = {
        {2.4, "NAME1", 24, 100},
        {3.4, "NAME2", 34, 200},
        {4.4, "NAME3", 44, 400},
        {5.4, "NAME4", 25, 5400},
        {6.4, "NAME5", 28, 600}
    };

    fwrite(arr, sizeof(struct student_t), 4, f_ptr);


    /*
    char r_arr[strlen(arr)];
    fread(r_arr, sizeof(char), strlen(arr), f_ptr);
    fwrite(r_arr, sizeof(char), strlen(arr), stdout);
    */

    fclose(f_ptr);
    
    return 0;
}
