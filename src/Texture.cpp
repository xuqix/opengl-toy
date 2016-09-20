#include "Texture.h"
#include "GL.h"
#include "DebugHelper.h"

struct Texture::PrivateData
{
    Size size = Size(0, 0);
    GLuint texture = -1;
};

Texture::Texture(Image * image):_data(new PrivateData())
{
    _data->size.width = image->getWidth();
    _data->size.height = image->getHeight();

    // gen and bind texture
    glGenTextures(1, &_data->texture);
    glBindTexture(GL_TEXTURE_2D, _data->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    delete _data;
}

const Texture::Size & Texture::getContentSize() const
{
    return _data->size;
}

int Texture::object() const
{
    return (int)_data->texture;
}

void Texture::active() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _data->texture);
}

