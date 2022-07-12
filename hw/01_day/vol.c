#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARG_COUNT 4
#define INVALID_PARAM_ERR_CODE -1
#define INVALID_PARAM_ERR_MSG "Usage: ./vol radius<double> height<double> length<double>\n"
#define MIN_RADIUS_VAL 0
#define MIN_HEIGHT_VAL 0
#define MIN_LEN_VAL 0

void help();

int main (int argc, char *argv[])
{
        double radius, height, length;
        double vol_vertical, vol_horizontal;

        if (argc != ARG_COUNT) {
                help();
                return INVALID_PARAM_ERR_CODE;
        }

        radius = strtod(argv[1], NULL);
        height = strtod(argv[2], NULL);
        length = strtod(argv[3], NULL);

        if (radius < MIN_RADIUS_VAL || radius == 0 || height == 0 || height < MIN_HEIGHT_VAL || length == 0 || length < MIN_LEN_VAL) {
                help();
                return INVALID_PARAM_ERR_CODE;
        }

        vol_vertical = M_PI * pow(radius, 2) * height;

        // https://www.mathsisfun.com/geometry/cylinder-horizontal-volume.html
        vol_horizontal = (acos((radius - height)/radius) * pow(radius, 2) - (radius - height)*sqrt(2*radius*height - pow(height, 2))) * length;


        printf("vol_vertical - %lf\nvol_horizontal - %lf\n", vol_vertical, vol_horizontal);

        return 0;
}

void help() {
        printf(INVALID_PARAM_ERR_MSG);
}
