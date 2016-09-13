#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader
{
public:
    Shader();

    ~Shader();

    bool initWithFile(const std::string &vertexPath, const std::string &fragmentPath);

    bool initWithString(const std::string &vertexCode, const std::string &fragmentCode);

    // Uses the current shader
    void use();

private:
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    struct PrivateData;
    PrivateData *_data;
};

#endif
