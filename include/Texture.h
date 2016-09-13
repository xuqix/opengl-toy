#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Image.h"
#include "mathlib.h"

class Texture
{
    typedef glm::Size Size;
public:
    Texture(Image *image);

    ~Texture();

    const Size& getContentSize() const;

    int object() const;

private:
    Texture(const Texture&);
    Texture& operator=(const Texture&);

    struct PrivateData;
    PrivateData *_data;
};

#endif
