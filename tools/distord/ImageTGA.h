//
// Created by fabien sanglard on 2016-11-12.
//

#ifndef TOVGAPLANES_IMAGETGA_H
#define TOVGAPLANES_IMAGETGA_H


#include <cstdio>

class ImageTGA {
public:

    ImageTGA();
    ~ImageTGA();

    void Init(const char* base, const char* filename);
    uint8_t* GetPixels() { return this->colorPixels;}

    size_t width;
    size_t height;
    char filename[512];

private:
    size_t bpp;
    char fullPath[512];
    uint8_t* colorPixels;
};


#endif //TOVGAPLANES_IMAGETGA_H
