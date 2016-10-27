#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdio>

#include "mathlib.h"

#define UNUSED_PARAM(var) (void)(var)

namespace Utils {

    inline void print(const std::string &str)
    {
        std::cout << str << std::endl;
    }

    inline void print(const glm::vec2 &v)
    {
        printf("%.2f, %.2f\n", v.x, v.y);
    }

    inline void print(const glm::vec3 &v)
    {
        printf("%.2f, %.2f, %.2f\n", v.x, v.y, v.z);
    }

    inline void print(const glm::vec4 &v)
    {
        printf("%.2f, %.2f, %.2f, %.2f\n", v.x, v.y, v.z, v.w);
    }

    inline void print(const glm::mat4 &trans)
    {
        for(int i=0; i<4; i++)
            print(trans[i]);
    }
}

#endif
