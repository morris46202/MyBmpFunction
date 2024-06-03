#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<unistd.h>
#include<stddef.h>

#define DEBUG 0
#define HI if(DEBUG) printf("HI\n");
#define XD if(DEBUG)

typedef struct mypixel{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}mypixel;


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

void print_header( bmpheader bmp )
{
    printf("bfType: %c", bmp.bfType[0]);
    printf("%c\n", bmp.bfType[1]);
    printf("bfSize: %d\n", bmp.bfSize);
    printf("bfReserved1: %d\n", bmp.bfReserved1);
    printf("bfReserved2: %d\n", bmp.bfReserved2);
    printf("bfOffBytes: %d\n", bmp.bfOffBytes);
    printf("biSize: %d\n", bmp.biSize);
    printf("biWidth: %d\n", bmp.biWidth);
    printf("biHeight: %d\n", bmp.biHeight);
    printf("biPlanes: %d\n", bmp.biPlanes);
    printf("biBitCount: %d\n", bmp.biBitCount);
    printf("biCompression: %d\n", bmp.biCompression);
    printf("biSizeImage: %d\n", bmp.biSizeImage);
    printf("biXPelsPerMeter: %d\n", bmp.biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n", bmp.biYPelsPerMeter);
    printf("biClrUsed: %d\n", bmp.biClrUsed);
    printf("biClrImportant: %d\n", bmp.biClrImportant);
}

// init_mypixel
mypixel **init_mypixel(int width, int height)
{
    mypixel **pixel = (mypixel **)malloc(sizeof(mypixel *) * height);
    for(int i = 0; i < height; i++)
    {
        pixel[i] = (mypixel *)malloc(sizeof(mypixel) * width);
    }
    return pixel;
}
// file_to_mypixel
void file_to_mypixel(FILE *fp , int width, int height , mypixel **pixel)
{
    fseek(fp, 0, SEEK_SET);
    bmpheader header;
    fread(&header,sizeof(bmpheader),1,fp);
    fseek(fp, header.bfOffBytes, SEEK_SET);
    for(int i = height - 1; i >= 0; i--)
    {
        for(int j = 0; j < width; j++){
            fread(&pixel[i][j], sizeof(mypixel), 1, fp);
        }
        // padding
        if((width * 3) % 4 != 0)
        {
            fseek(fp, 4 - (width * 3) % 4, SEEK_CUR);
            HI
        }
    }

}

// mypixel_to_file
void mypixel_to_file(bmpheader header, mypixel **pixel, int width, int height, FILE *fp)
{
    fseek(fp, 0, SEEK_SET);
    fwrite(&header, sizeof(bmpheader), 1, fp);
    fseek(fp, header.bfOffBytes, SEEK_SET);
    for(int i = height - 1; i >= 0; i--)
    {
        for(int j = 0; j < width; j++)
        {
            fwrite(&pixel[i][j], sizeof(mypixel), 1, fp);
        }
        // padding
        if((width * 3) % 4 != 0)
        {
            uint8_t padding = 0;
            //fwrite(&padding, 1, 4 - (width * 3) % 4, fp);
            fseek(fp, 4 - (width * 3) % 4, SEEK_CUR);
            XD printf("padding\n");
        }
    }
}
// set_all_color
mypixel **set_all_color(mypixel **pixel, int width, int height, uint8_t r, uint8_t g, uint8_t b)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel[i][j].r = r;
            pixel[i][j].g = g;
            pixel[i][j].b = b;
        }
    }
    return pixel;
}
// set_pixel_color
mypixel **set_pixel_color(mypixel **pixel, int width, int height, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    pixel[y][x].r = r;
    pixel[y][x].g = g;
    pixel[y][x].b = b;
    return pixel;
}
// get_pixel_color
mypixel get_pixel_color(mypixel **pixel, int width, int height, int x, int y)
{
    return pixel[y][x];
}
// free_mypixel
void free_mypixel(mypixel **pixel, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        free(pixel[i]);
    }
    free(pixel);
}
// rotate_mypixel
mypixel **rotate_mypixel(mypixel **pixel, int width, int height)
{
    mypixel **new_pixel = init_mypixel(height, width);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            new_pixel[j][height - i - 1] = pixel[i][j];
        }
    }
    return new_pixel;

}
// v_flip_mypixel
mypixel **v_flip_mypixel(mypixel **pixel, int width, int height)
{
    mypixel **new_pixel = init_mypixel(width, height);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            new_pixel[i][j] = pixel[height - i - 1][j];
        }
    }
    return new_pixel;
}
// h_flip_mypixel
mypixel **h_flip_mypixel(mypixel **pixel, int width, int height)
{
    mypixel **new_pixel = init_mypixel(width, height);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            new_pixel[i][j] = pixel[i][width - j - 1];
        }
    }
    free(pixel);
    return new_pixel;
}




