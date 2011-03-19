/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#ifndef TEXTURE_H
#define TEXTURE_H


#include "ofMain.h"

class Texture {
    private:
        unsigned int id;
    public:
        Texture();
        ~Texture();
        void bind();
        void unbind();
        void load(ofImage &image, int wrapS, int wrapT);
};
#endif // TEXTURE_H
