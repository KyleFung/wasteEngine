#include <Texture.h>

Texture::Texture(GLenum target, std::string& fileName)
{
    mFileName = fileName;
    mTextureTarget = target;
}

bool Texture::load()
{
    try
    {
        //Use ImageMagick to read file and write to blob
        mImage.read(mFileName);
        mImage.write(&mBlob, "RGBA");
    }
    catch(Magick::Error& e)
    {
        std::cout << "Couldn't read " << mFileName << ": " << e.what() << "\n";
        return false;
    }

    glGenTextures(1, &mTextureObj);
    glBindTexture(mTextureTarget, mTextureObj);
    glTexImage2D(mTextureTarget, 0, GL_RGBA, mImage.columns(), mImage.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mBlob.data());
    glTexParameterf(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(mTextureTarget, 0);

    return true;
}

void Texture::bind(GLenum texUnit)
{
    glActiveTexture(texUnit);
    glBindTexture(mTextureTarget, mTextureObj);
}
