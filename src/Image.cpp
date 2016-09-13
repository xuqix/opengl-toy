#include "Image.h"

#include <fstream>

#include "SOIL.h"

static bool isPng(const std::string &path)
{
    std::ifstream in(path.c_str());
    if(!in) return false;

    in.seekg(0, std::ios_base::end);
    int dataLen = in.tellg();
    if (dataLen <= 8)
        return false;

    in.seekg(0, std::ios_base::beg);
    char buff[10] = { 0 };
    in.read(buff, 8);
    in.close();
    static const unsigned char PNG_SIGNATURE[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
    return memcmp(PNG_SIGNATURE, buff, sizeof(PNG_SIGNATURE)) == 0;
}

struct Image::PrivateData
{
    Image::Format format = Image::Format::NONE;

    int width = 0;
    int height = 0;
    int dataLen = 0;
    unsigned char *data = nullptr;
};

Image::Image(const std::string & path):_data(new PrivateData())
{
    if(isPng(path))
    {
        int width, height;
        unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        if(image)
        {
            _data->width = width;
            _data->height = height;
            _data->dataLen = width * height;
            _data->data = image;
            _data->format = Format::PNG;
        }
    }
}

Image::~Image()
{
    if(_data->data) SOIL_free_image_data(_data->data);
    delete _data;
}

int Image::getWidth() const
{
    return _data->width;
}

int Image::getHeight() const
{
    return _data->height;
}

const unsigned char* Image::getData() const
{
    return _data->data;
}

int Image::getDataLen() const
{
    return _data->dataLen;
}

Image::Format Image::getFormat() const
{
    return _data->format;
}

