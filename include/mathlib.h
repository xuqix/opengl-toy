#ifndef _MATH_H_
#define _MATH_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace glm
{
    typedef vec2 Vec2;
    typedef vec3 Vec3;
    typedef vec4 Vec4;
    typedef mat4 Mat4;

    class Size
    {
    public:
        float width;
        float height;

        operator Vec2() const
        {
            return Vec2(width, height);
        }

        Size():width(0), height(0) {}

        Size(float width_, float height_):width(width_), height(height_) {}

        Size(const Vec2 &v):width(v.x), height(v.y) {}

        Size(const Size &o):width(o.width), height(o.height) {}

        Size& operator=(const Size &o)
        {
            this->width = o.width;
            this->height = o.height;
            return *this;
        }

        Size& operator=(const Vec2 &v)
        {
            this->width = v.x;
            this->height = v.y;
            return *this;
        }

        bool operator==(const Size &o)
        {
            return (std::fabs(o.width - o.width)) < FLT_EPSILON && (std::fabs(o.height - o.height)) < FLT_EPSILON;
        }

        bool operator!=(const Size &o)
        {
            return !(*this == o);
        }

        static const Size& ZERO()
        {
            static const Size _zero = Size(0, 0);
            return _zero;
        }
    };

    class Rect
    {
    public:
        Vec2 origin;
        Size size;

        Rect():origin(Vec2(0, 0)), size(Size(0, 0)) {}

        Rect(float x, float y, float width, float height):origin(Vec2(x, y)), size(Size(width, height)) {}

        Rect(const Vec2 &pos, const Size &size)
        {
            setRect(pos.x, pos.y, size.width, size.height);
        }

        Rect(const Rect &o)
        {
            setRect(o.origin.x, o.origin.y, o.size.width, o.size.height);
        }

        Rect& operator=(const Rect &o)
        {
            setRect(o.origin.x, o.origin.y, o.size.width, o.size.height);
            return *this;
        }

        bool operator==(const Rect &o)
        {
            return (origin == o.origin) && (size == o.size);
        }

        bool operator!=(const Rect &o)
        {
            return !(*this == o);
        }

        void setRect(float x, float y, float width, float height)
        {
            origin = Vec2(x, y);
            size = Size(width, height);
        }
    };
};

#endif
