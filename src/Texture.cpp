/*
    Effet Ball - QPT1
    Andreas Stallinger - Programmer
    MultiMediaTechnology
    FH Salzburg
*/

#include "Texture.h"


Texture::Texture(){
    glGenTextures(1,&id);
}

void Texture::bind(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0); // unbind texture
    glDisable(GL_TEXTURE_2D);
}

void Texture::load(ofImage &image, int wrapS, int wrapT){
    Texture::bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    unsigned char *pixels = image.getPixels();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    gluBuild2DMipmaps(
                        GL_TEXTURE_2D,
                        GL_RGB,
                        image.getWidth(), image.getHeight(),
                      GL_RGB,GL_UNSIGNED_BYTE,
                      pixels
                      );
    Texture::unbind();
}

Texture::~Texture(){
    glDeleteTextures(1, &id);
}
