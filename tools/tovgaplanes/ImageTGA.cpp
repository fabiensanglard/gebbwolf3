//
// Created by fabien sanglard on 2016-11-12.
//

#include <cstring>
#include <cstdint>
#include <cstdlib>
#include "ImageTGA.h"
#include "ByteStream.h"


ImageTGA::ImageTGA(): colorPixels(nullptr){
}

#define TARGA_HEADER_SIZE 18
#define TARGA_FOOTER_SIZE 26
#define TARGA_FOOTER_SIGNATURE_OFFSET 8
#define TARGA_SCANLINE_OFFSET 490

void ImageTGA::Init(const char* base, const char* filename){

    fullPath[0] = '\0';
    strcat(this->fullPath, base);
    strcat(this->fullPath, filename);

    strncpy(this->filename, filename,512);

    printf("ImageTGA::Init => Loading file '%s'.\n",fullPath);

    FILE* file = fopen(fullPath, "rb");

    if (file == NULL){
        printf("ImageTGA::Init => Unable to open image '%s'.\n",fullPath);
        return;
    }

    //Get size of the file on HD:
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file,0 , SEEK_SET);

    if (size < TARGA_HEADER_SIZE){
        printf("ImageTGA::Init => File found '%s' but not a valid TGA header was found.\n",fullPath);
        return;
    }


    //Read full file content to RAM
    uint8_t* targaContent = (uint8_t*)calloc(size,sizeof(uint8_t));
    fread(targaContent, size, 1, file);

    //Check if wer are dealing with an Original TGA or a New TGA Format
    bool isNewTarga = false;
    size_t extensionAreaOffset = 0;
    size_t developerDirectoyOffset = 0;
    uint32_t* scanlineTable = NULL;

    if (size >= (TARGA_HEADER_SIZE + TARGA_FOOTER_SIZE))
    {
        ByteStream scanner;
        scanner.Set(targaContent+size-TARGA_FOOTER_SIZE+TARGA_FOOTER_SIGNATURE_OFFSET);
        const char* signatureLoc = (const char*)scanner.GetPosition();
        if (!strncmp(signatureLoc, "TRUEVISION-XFILE", 16)){


            isNewTarga = true;

            printf("    isNewTarga = %d\n",isNewTarga);

            scanner.Set(targaContent+size-TARGA_FOOTER_SIZE);

            extensionAreaOffset = scanner.ReadInt32LE();
            printf("    extensionAreaOffset = %ld\n",extensionAreaOffset);

            developerDirectoyOffset = scanner.ReadInt32LE();
            printf("    developerDirectoyOffset = %ld\n",developerDirectoyOffset);

            // The developer directory is interesting because it may contains the scanline table
            // which help to load the image not up side down.
            scanner.Set(targaContent+developerDirectoyOffset);
            size_t developerDirectorySize = scanner.ReadUShort();
            printf("    developerDirectorySize = %ld\n",developerDirectorySize);

            if(developerDirectorySize > 0){
                scanner.MoveForward(TARGA_SCANLINE_OFFSET);
                size_t scanLineTableOffset = scanner.ReadInt32LE();

                //There is a scanline table. Here it is.
                scanner.Set(targaContent + scanLineTableOffset);
                scanlineTable = (uint32_t*)scanner.GetPosition();
            }
        }
    }
    else
        printf("    isNewTarga = %d\n",isNewTarga);


    if (scanlineTable != NULL){
        printf("ImageTGA::Init => File found '%s' but it features a scanline table which is not supported.\n",fullPath);
        return;
    }

    //Header structure header
    /*
     typedef struct {
     char  idlength;
     char  colourmaptype;
     char  datatypecode;
     short int colourmaporigin;
     short int colourmaplength;
     char  colourmapdepth;
     short int x_origin;
     short int y_origin;
     short width;
     short height;
     char  bitsperpixel;
     char  imagedescriptor;
     } HEADER;
    */

    ByteStream s;
    s.Set(targaContent);
    uint8_t idlength = s.ReadByte(); // idlength
    //printf("    idlength = %d\n",idlength);

    uint8_t colourmaptype = s.ReadByte(); // colourmaptype
    //printf("    colourmaptype=%d\n",colourmaptype);


    /*
     0 no image data is present
     1 uncompressed color-mapped image
     2 uncompressed true-color image
     3 uncompressed black-and-white (grayscale) image
     9 run-length encoded color-mapped image
     10 run-length encoded true-color image
     11 run-length encoded black-and-white (grayscale) image
     */
    uint8_t datatypecode = s.ReadByte();
    printf("    datatypecode=%d\n",colourmaptype);

    if (datatypecode != 2){
        printf("ImageTGA::Init => File found '%s' but type is %u. Videa only support 'uncompressed true-color image RGB(A)' (type 2).\n",fullPath,datatypecode);
        return;
    }


    s.ReadShort();// colourmaporigin
    //printf("    colourmaporigin=%d\n",colourmaporigin);

    s.ReadShort();// colourmaplength
    //printf("    colourmaplength=%d\n",colourmaplength);

    s.ReadByte(); // colourmapdepth
    //printf("    colourmapdepth=%d\n",colourmapdepth);

    s.ReadShort();// x_origin
    //printf("    x_origin=%d\n",x_origin);

    s.ReadShort();// y_origin
    //printf("    y_origin=%d\n",y_origin);

    //Dimension are little endian but let's still load them in a portable way:
    this->width = s.ReadByte();
    this->width = this->width | (s.ReadByte() << 8);

    this->height = s.ReadByte();
    this->height = this->height | (s.ReadByte() << 8);


    uint32_t bitsPerPixel = s.ReadByte();
    this->bpp = bitsPerPixel / 8;

    uint32_t imageDesc = s.ReadByte();

    bool needVflip = (imageDesc & 0x20) == 0;
    bool needHflip = (imageDesc & 0x10) == 0x10;

    /*
          Origin is well represented in Targa specs:

           First pixel position    bit 0x20   bit 0x10

            bottom left               0           0
            bottom right              0           1
            top    left               1           0
            top    right              1           1
     */

    printf("    needVflip=%d\n",needVflip);

    if (needHflip){
        printf("File found '%s' but requires Hflip which is not implemented.\n",fullPath);
        return;

    }
    else
        printf("    needHflip=%d\n",needHflip);



    if ( bpp != 4 && bpp != 3){
        printf("File found '%s' with 'uncompressed true-color image RGB(A)' but unsupported bpp (%zu) supported are 24 and 32.\n",fullPath, bpp);
        return;
    }


    printf("Found TARGA at '%s' type=%d width=%lu, height=%lu bbp=%zu.\n",fullPath,datatypecode,this->width,this->height,bpp);


    //If the TARGA has an Identification Field we need to skip it.
    if (idlength > 0 )
        s.MoveForward(idlength);

    //Copy color data
    this->colorPixels = new uint8_t[this->width*this->height*3];




    //Depending on the scanline order, we need to flip the targa upside down.


    //We need to reverse color  since TGA has a BGR channel order and we need RGB

    uint8_t* dst = colorPixels;

    for(size_t i = 0 ; i < this->height ; i ++ ){
        uint8_t* src;
        if (needVflip)
            src = (uint8_t*)(s.GetPosition() + this->height* this->width * bpp - i * this->width * bpp);
        else
            src = (uint8_t*)(s.GetPosition() + i * this->width * bpp);


        //Now copy all pixels for that line
        for (size_t j=0; j < this->width ; j++) {


            uint8_t b = *src++;
            uint8_t g = *src++;
            uint8_t r = *src++;

            if (bpp ==4)
                /*uint8_t a = **/src++;

            dst[0] = r;
            dst[1] = g;
            dst[2] = b;
            //dst[3] = a;
            dst+=3;
        }
    }

    this->bpp = 3;

    free(targaContent);
    fclose(file);

}

ImageTGA::~ImageTGA() {
    delete[] colorPixels;
    colorPixels = NULL;
}
