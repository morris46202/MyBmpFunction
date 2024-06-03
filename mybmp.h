#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

struct _bmpheader{
    char bfType[2];            // 2 bytes , in windows it is "BM"
    uint32_t bfSize;            // 4 bytes
    uint16_t bfReserved1;       // 2 bytes
    uint16_t bfReserved2;       // 2 bytes
    uint32_t bfOffBytes;         // 4 bytes
    // infomation header
    uint32_t biSize;            // 4 bytes
    int32_t biWidth;            // 4 bytes
    int32_t biHeight;           // 4 bytes
    uint16_t biPlanes;          // 2 bytes
    uint16_t biBitCount;        // 2 bytes
    uint32_t biCompression;     // 4 bytes
    uint32_t biSizeImage;       // 4 bytes , size of image or data size
    uint32_t biXPelsPerMeter;   // 4 bytes , H-resolution
    uint32_t biYPelsPerMeter;   // 4 bytes , V-resolution
    uint32_t biClrUsed;         // 4 bytes , number of color used
    uint32_t biClrImportant;    // 4 bytes , number of important color

}__attribute__((__packed__));
typedef struct _bmpheader bmpheader;


typedef struct mypixel{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}mypixel;


void print_header( bmpheader bmp );

// init_mypixel
mypixel **init_mypixel(int width, int height);
// file_to_mypixel
void file_to_mypixel(FILE *fp , int width, int height, mypixel **pixel);
// mypixel_to_file
void mypixel_to_file(bmpheader header, mypixel **pixel, int width, int height, FILE *fp);
// set_all_color
mypixel **set_all_color(mypixel **pixel, int width, int height, uint8_t r, uint8_t g, uint8_t b);
// set_pixel_color
mypixel **set_pixel_color(mypixel **pixel, int width, int height, int x, int y, uint8_t r, uint8_t g, uint8_t b);
// get_pixel_color
mypixel get_pixel_color(mypixel **pixel, int width, int height, int x, int y);
// free_mypixel
void free_mypixel(mypixel **pixel, int width, int height);
// rotate_mypixel
mypixel **rotate_mypixel(mypixel **pixel, int width, int height);
// v_flip_mypixel
mypixel **v_flip_mypixel(mypixel **pixel, int width, int height);
// h_flip_mypixel
mypixel **h_flip_mypixel(mypixel **pixel, int width, int height);

