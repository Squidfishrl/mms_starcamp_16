#ifndef _BITWISE_OPERATIONS_H_
#define _BITWISE_OPERATIONS_H_

#include <stdint.h>

int add_attendance(uint32_t *attendance, int student_num);
int remove_attendance(uint32_t *attendance, int student_num);
void print_non_attendants(uint32_t attendance);
void print_attendants(uint32_t attendance);
int change_attendance(uint32_t *attendance, int student_num);

#endif // !_BITWISE_OPERATIONS_H_
