#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "ppm.h"

uint8_t _rgb_to_mask(char *rgb_str);

int main (int argc, char *argv[])
{
        if (argc < 3) {
                fprintf(stderr, "Insufficient amount of arguments, expected input_image.ppm output_image.ppm\nOrder of parameters should also make a difference (-g and -f)\n");
                return EXIT_FAILURE;
        }

        PPM_Image_Buffer buf;
        if (read_ppm_color_bitmap(argv[1], &buf)) {
                perror("read_ppm_color_bitmap");
                return EXIT_FAILURE;
        }

        char output_file[strlen(argv[2])];
        strcpy(output_file, argv[2]);

        int opt;
        while ((opt = getopt(argc, argv, "gf:")) != -1) {
                switch(opt) {
                case 'g':
                        convert_to_grayscale(&buf);
                        break;
                case 'f':;
                        uint8_t mask = _rgb_to_mask(optarg);
                        if (mask > 7) {
                                fprintf(stderr, "Invalid argument %s\n", optarg);
                                return EXIT_FAILURE;
                        }

                        filter_color_component(&buf, mask);
                        break;
                }
        }

        if (write_ppm_color_bitmap(output_file, &buf)) {
                perror("write_ppm_color_bitmap");
                return -1;
        }

        free(buf.data);

        return 0;
}

uint8_t _rgb_to_mask(char *rgb_str)
{
        uint8_t mask = 0;
        while(*rgb_str != '\0') {
                if (*rgb_str == 'r')
                        mask |= 0b001;
                else if (*rgb_str == 'g')
                        mask |= 0b010;
                else if (*rgb_str == 'b')
                        mask |= 0b100;
                else
                        return 255;

                rgb_str++;
        }

        return mask;
}
