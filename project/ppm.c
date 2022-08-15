#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"


int read_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf)
{
        FILE *fp = fopen(filename, "r");
        if (NULL == fp)
                return -1;

        // read and verify first line
        char line1[LINE1_CHARS];
        if (fread(&line1, sizeof(char), LINE1_CHARS, fp) != LINE1_CHARS)
                return -1;

        line1[LINE1_CHARS - 1] = '\0';
        if (strcmp(line1, PPM_FIRST_LINE_HEADER))
                return -1;

        // get width and height
        int width, height;
        if (fscanf(fp, "%d %d\n", &width, &height) != 2)
                return -1;

        if (width <= 0 || height <= 0)
                return -1;

        buf->coln = width;
        buf->rown = height;
        int pixels = width * height;

        buf->data = malloc(sizeof(Pixel_Data) * pixels);
        if (NULL == buf->data)
                return -1;

        // read line 3 which should always be 255
        char line3[LINE3_CHARS];
        if (fread(line3, sizeof(char), LINE3_CHARS, fp) != LINE3_CHARS)
                return -1;

        line3[LINE3_CHARS - 1] = '\0';

        if (strcmp(line3, LINE3_EXTRA_ARGS))
                return -1;

        // read image pixels by pixel
        int red, green, blue;
        for (int i = 0; i < pixels; i++) {
                if (fscanf(fp, "%d %d %d\n", &red, &green, &blue) != 3)
                        return -1;

                buf->data[i].red = red;
                buf->data[i].green = green;
                buf->data[i].blue = blue;
        }

        fclose(fp);
        return 0;
}

int write_ppm_color_bitmap(char *filename, PPM_Image_Buffer *buf)
{
        FILE *fp = fopen(filename, "wb");
        if (NULL == fp)
                return -1;

        fprintf(fp, "P3\n%d %d\n255\n", buf->coln, buf->rown);

        for (int i = 0, pixels = buf->coln * buf->rown; i < pixels; i++) {
                fprintf(fp, "%d %d %d\n", buf->data[i].red, buf->data[i].green, buf->data[i].blue);
        }

        if (ferror(fp))
                return -1;

        fclose(fp);

        return 0;

}

void filter_color_component(PPM_Image_Buffer *buf, unsigned int rgb_mask)
{
        uint8_t red, green, blue;
        red   = 0b001 & rgb_mask;
        blue  = 0b010 & rgb_mask;
        green = 0b100 & rgb_mask;

        for (int i = 0, pixels = buf->rown * buf->coln; i < pixels; i++) {
                if (0 == red)
                        buf->data[i].red = 0;
                if (0 == blue)
                        buf->data[i].blue = 0;
                if (0 == green)
                        buf->data[i].green = 0;
        }
}

void convert_to_grayscale(PPM_Image_Buffer *buf)
{
        for (int i = 0, pixels = buf->rown * buf->coln; i < pixels; i++) {
                // get highest colour value (red, green or blue) and apply it to all other colour streams
                buf->data[i].red = buf->data[i].red * 0.299 + buf->data[i].green * 0.587 + buf->data[i].blue * 0.114;
                buf->data[i].green = buf->data[i].red;
                buf->data[i].blue = buf->data[i].red;
        }

}

int write_ppm_color_bitmap_bin(char *filename, PPM_Image_Buffer *buf)
{
        FILE *fp = fopen(filename, "wb");
        if (NULL == fp)
                return -1;

        fprintf(fp, "P6\n%d %d\n255\n", buf->coln, buf->rown);

        if (fwrite(buf, sizeof(Pixel_Data), buf->coln * buf->rown, fp) != buf->coln * buf->rown)
                return -1;

        fclose(fp);

        return 0;
}
