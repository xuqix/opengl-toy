#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>

class Image
{
public:
    enum class Format
    {
        NONE,
        PNG
    };

    Image(const std::string &path);

    ~Image();

    int getWidth() const;

    int getHeight() const;

    const unsigned char* getData() const;

    int getDataLen() const;

    Format getFormat() const;

private:
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    struct PrivateData;
    PrivateData *_data;
};

#endif
