#ifndef __PPM_H__ 
#define __PPM_H__

#include <stdint.h>

#define LINE1_CHARS 3
#define PPM_FIRST_LINE_HEADER "P3"
#define LINE3_CHARS 4
#define LINE3_EXTRA_ARGS "255"

typedef struct pixel_t {

        uint8_t red;
        uint8_t green;
        uint8_t blue;
} Pixel_Data;

typedef struct PPM_Image_Buffer {
        Pixel_Data *data;
        int rown, coln;
} PPM_Image_Buffer;


int read_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf);
int write_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf);
int write_ppm_color_bitmap_bin(char *filename, PPM_Image_Buffer *buf);
void filter_color_component(PPM_Image_Buffer *buf, unsigned int rgb_mask);
void convert_to_grayscale(PPM_Image_Buffer *buf);

#endif // !__PPM_H__
