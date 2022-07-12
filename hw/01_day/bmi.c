#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARG_COUNT 3
#define INVALID_PARAM_ERR_CODE -1
#define INVALID_PARAM_ERR_MSG "Usage: ./bmi weight<double> height<double>\n"
#define MIN_MASS_VAL 1
#define MIN_HEIGHT_VAL 1

void help();

int main (int argc, char *argv[])
{
        double mass, height;
        double bmi_new, bmi_old;

        if (argc != ARG_COUNT) {
                help();
                return INVALID_PARAM_ERR_CODE;
        }

        mass = strtod(argv[1], NULL);
        height = strtod(argv[2], NULL);

        if (mass < MIN_MASS_VAL || mass == 0 || height == 0 || height < MIN_HEIGHT_VAL) {
                help();
                return INVALID_PARAM_ERR_CODE;
        }

        bmi_old = mass / pow(height, 2);
        bmi_new = 1.3 * mass / powf(height, 2.5);

        printf("bmi_old - %lf\nbmi_new - %lf\n", bmi_old, bmi_new);

        return 0;
}

void help() {
        printf(INVALID_PARAM_ERR_MSG);
}
