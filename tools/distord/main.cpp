#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "ImageTGA.h"

#define OFFSET ((320*100+100)*3)
void GenerateOuput(ImageTGA& pTGA) {
    int numBytesInImage = pTGA.width * pTGA.height * 3;
   uint8_t* data = new uint8_t[numBytesInImage];

    for(int32_t p=0; p < numBytesInImage; p+=3) {
        data[numBytesInImage-p] =   pTGA.GetPixels()[(p+2+OFFSET)%numBytesInImage];
        data[numBytesInImage-p+1] = pTGA.GetPixels()[(p+1+OFFSET)%numBytesInImage];
        data[numBytesInImage-p+2] = pTGA.GetPixels()[(p+0+OFFSET)%numBytesInImage];
    }

    uint8_t header[18];
    memset(header,0,18);
    header[2] = 2; // uncompressed, true-color image
    header[12] = pTGA.width & 0x00FF ;
    header[13] = (pTGA.width & 0xFF00) / 256 ;
    header[14] = pTGA.height & 0x00FF ;
    header[15] = (pTGA.height & 0xFF00) / 256 ;
    header[16] = 24;

    char dst_filename[1024];
    memset(dst_filename, 0 , 1024);
    strcat(dst_filename, pTGA.filename);
    strcat(dst_filename, ".tga");
    printf("Writing output '%s'.\n", dst_filename);
    FILE* f = fopen(dst_filename, "w");
    fwrite(header, 1, sizeof(header), f);
    fwrite(data, pTGA.height * pTGA.width * 3, 1, f);
    fclose(f);
}



int main(int argc, char** argv) {

    if (argc < 1) {
        printf("Usage: %s <tga_to_convert>", argv[0]);
        return 1;
    }

    char* src_file = argv[1];
    printf("Processing images %s.\n", src_file);

    ImageTGA tga ;
    tga.Init("", src_file);

    GenerateOuput(tga);

    return 0;
}

