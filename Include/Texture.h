#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <Magick++.h>

class Texture
{
    public:
       Texture(GLenum target, std::string& fileName);
       Texture(){}
       bool load();
       void bind(GLenum texUnit);

    private:
       std::string mFileName;
       GLenum mTextureTarget;
       GLuint mTextureObj;

       Magick::Image mImage;
       Magick::Blob mBlob;
};

#endif
