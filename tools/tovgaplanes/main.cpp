#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "ImageTGA.h"

#define NUM_VGA_BANKS 4
#define BBP 3
void PopulateBank(uint8_t *data, ImageTGA& image, int padding, int bank) {

    size_t src_width = image.width;
    size_t src_height = image.height;
    size_t src_byte_per_row = image.width * BBP;
    size_t dst_byte_per_row = (image.width + padding*(NUM_VGA_BANKS-1)) * BBP;

    for (int i=bank ; i < src_width; i+=NUM_VGA_BANKS) {
        uint8_t* dst_pixel = data + (src_width/NUM_VGA_BANKS + padding)*bank*BBP + i/NUM_VGA_BANKS*BBP;
        uint8_t* src_pixel = image.GetPixels() + i * BBP;

        dst_pixel += (src_height-1) * dst_byte_per_row;
        for (int j=0 ; j < src_height ; j++) {
            dst_pixel[0] = src_pixel[2];
            dst_pixel[1] = src_pixel[1];
            dst_pixel[2] = src_pixel[0];
            dst_pixel -= dst_byte_per_row;
            src_pixel += src_byte_per_row;
        }
    }
}

void GenerateOuput(ImageTGA& pTGA, int padding) {
   uint8_t* data = new uint8_t[pTGA.width * pTGA.height + 3 * padding * pTGA.height];

    size_t dst_height = pTGA.height;
    size_t dst_widht = pTGA.width + 3 * padding;


    for(int bank=0 ; bank < NUM_VGA_BANKS ; bank++) {
        PopulateBank(data, pTGA, padding, bank);
    }

    uint8_t header[18];
    memset(header,0,18);
    header[2] = 2; // uncompressed, true-color image
    header[12] = dst_widht & 0x00FF ;
    header[13] = (dst_widht & 0xFF00) / 256 ;
    header[14] = dst_height & 0x00FF ;
    header[15] = (dst_height& 0xFF00) / 256 ;
    header[16] = 24;

    char dst_filename[1024];
    memset(dst_filename, 0 , 1024);
    strcat(dst_filename, pTGA.filename);
    strcat(dst_filename, ".tga");
    FILE* f = fopen(dst_filename, "w");
    fwrite(header, 1, sizeof(header), f);
    fwrite(data, dst_widht * dst_height * 3, 1, f);
    fclose(f);
}



int main(int argc, char** argv) {

    if (argc < 2) {
        printf("Usage: %s <tga_to_convert> <padding>", argv[0]);
        return 1;
    }

    char* src_file = argv[1];
    int padding = atoi(argv[2]);
    printf("Processing images %s.\n", src_file);

    ImageTGA tga ;
    tga.Init("", src_file);

    GenerateOuput(tga, padding);

    return 0;
}

