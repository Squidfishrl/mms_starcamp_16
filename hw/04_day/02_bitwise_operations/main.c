#include <stdio.h>
#include <stdint.h>

#include "bitwise_operations.h"

void clean_stdin();
int get_student_num(size_t *student_num);

int main (int argc, char *argv[])
{
        uint32_t attendance = 0; 
        int option;
        while (1) {
                printf("1. Set attendance\n");
                printf("2. Clear attendance\n");
                printf("3. Attendance info\n");
                printf("4. Change attendance\n");
                printf("5. Exit\n");

                int scanf_option_code = scanf("%d", &option);

                if (EOF == scanf_option_code) {
                        return 0;
                } else if (1 != scanf_option_code) {
                        fprintf(stderr, "error: invalid argument\n");
                        clean_stdin();
                        continue;
                }



                size_t student_num;
                int get_option_code;
                switch (option) {
                case 1:

                        if ((get_option_code = get_student_num(&student_num))) {
                                fprintf(stderr, "error: invalid student num\n");
                                clean_stdin();
                                break;
                        } else if (-1 == get_option_code) {
                                return 0;
                        }

                        if (add_attendance(&attendance, student_num) == -1)
                                fprintf(stderr, "error: invalid student num\n");
                       

                        break;
                case 2:
                        if ((get_option_code = get_student_num(&student_num))) {
                                fprintf(stderr, "error: invalid student num\n");
                                clean_stdin();
                                break;
                        } else if (-1 == get_option_code) {
                                return 0;
                        }

                        if (remove_attendance(&attendance, student_num) == -1)
                                fprintf(stderr, "error: invalid student num\n");
                        break;
                case 3:
                        printf("Attending students:\n");
                        print_attendants(attendance);
                        printf("Non attending students:\n");
                        print_non_attendants(attendance);
                        break;
                case 4:
                        if ((get_option_code = get_student_num(&student_num))) {
                                fprintf(stderr, "error: invalid student num\n");
                                clean_stdin();
                                break;
                        } else if (-1 == get_option_code) {
                                return 0;
                        }

                        if (-1 == change_attendance(&attendance, student_num))
                                fprintf(stderr, "error: invalid student num\n");
                        break;
                case 5:
                        return 0;
                default:
                        fprintf(stderr, "error: invalid option\n");
                        break;
                }
        }
        return 0;
}

int get_student_num(size_t *student_num)
{
        printf("Enter student num: ");
        int get_code = scanf("%lu", student_num);

        if (EOF == get_code)
                return -1;
        else if (1 == get_code)
                return 0;
        else 
                return 1;

}

void clean_stdin()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
                continue;
        }
}
