#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>

#include "mathlib.h"

class Image;
class Texture;
class Shader;

class Sprite
{
public:
    Sprite();

    Sprite(const std::string &path);

    ~Sprite();

    virtual const glm::Vec3& getPosition() const;

    virtual void setPosition(const glm::Vec3 &pos);

    virtual const glm::Vec3& getRotation() const;

    virtual void setRotation(const glm::Vec3 &rotation);

    Image* getImage();

    Texture* getTexture();

    Shader* getShader();

    virtual void draw();

private:
    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

    struct PrivateData;
    PrivateData *_data;
};

#endif
