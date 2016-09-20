#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "mathlib.h"

class Texture;

class Shader
{
public:
    enum
    {
        VERTEX_POSITION,
        VERTEX_COLOR,
        VERTEX_TEXCOORD
    };

    enum class BuiltinShader
    {
        SHADER_POSITION_COLOR,
        SHADER_POSITION_COLOR_NO_MVP,
        SHADER_POSITION_COLOR_TEXTURE,
        SHADER_POSITION_COLOR_TEXTURE_NO_MVP
    };

    static const char* UNIFORM_M_MATRIX;
    static const char* UNIFORM_V_MATRIX;
    static const char* UNIFORM_P_MATRIX;
    static const char* UNIFORM_TEXTURE0;

    Shader();

    ~Shader();

    bool initWithBuiltin(BuiltinShader shaderType);

    bool initWithFile(const std::string &vertexPath, const std::string &fragmentPath);

    bool initWithString(const std::string &vertexCode, const std::string &fragmentCode);

    // Uses the current shader
    void use();

    int object() const;

    int getUniformLocation(const std::string &name);

    void setUniformValue(const std::string& uniformName, Texture *texture);

    void setUniformValue(const std::string& uniformName, int value);

    void setUniformValue(const std::string& uniformName, float value);

    void setUniformValue(const std::string& uniformName, const glm::Vec2& value);

    void setUniformValue(const std::string& uniformName, const glm::Vec3& value);

    void setUniformValue(const std::string& uniformName, const glm::Vec4& value);

    void setUniformValue(const std::string& uniformName, const glm::Mat4& value);

    void setUniformValuePointer(const std::string& uniformName, ssize_t size, const float* pointer);

    void setUniformValuePointer(const std::string& uniformName, ssize_t size, const glm::Vec2* pointer);

    void setUniformValuePointer(const std::string& uniformName, ssize_t size, const glm::Vec3* pointer);

    void setUniformValuePointer(const std::string& uniformName, ssize_t size, const glm::Vec4* pointer);

private:
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    struct PrivateData;
    PrivateData *_data;
};

#endif
