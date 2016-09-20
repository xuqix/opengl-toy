#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include "Texture.h"
#include "GL.h"

#include "Shader.ipp"

const char* Shader::UNIFORM_M_MATRIX = "model";
const char* Shader::UNIFORM_V_MATRIX = "view";
const char* Shader::UNIFORM_P_MATRIX = "projection";
const char* Shader::UNIFORM_TEXTURE0 = "texture0";

struct Shader::PrivateData
{
    GLuint program = 0;
};

Shader::Shader():_data(new Shader::PrivateData()) {}

Shader::~Shader()
{
    delete _data;
}

bool Shader::initWithBuiltin(BuiltinShader shaderType)
{
    switch(shaderType)
    {
        case BuiltinShader::SHADER_POSITION_COLOR:
            return initWithString(s_vertexPositionColor, s_fragmentPositionColor);

        case BuiltinShader::SHADER_POSITION_COLOR_TEXTURE:
            return initWithString(s_vertexPositionColorTexture, s_fragmentPositionColorTexture);

        case BuiltinShader::SHADER_POSITION_COLOR_NO_MVP:
            return initWithString(s_vertexPositionColorNoMVP, s_fragmentPositionColorNoMVP);

        case BuiltinShader::SHADER_POSITION_COLOR_TEXTURE_NO_MVP:
            return initWithString(s_vertexPositionColorTextureNoMVP, s_fragmentPositionColorTextureNoMVP);
    }
    return false;
}

bool Shader::initWithFile(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::stringstream vShaderStream, fShaderStream;

    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return false;
    }
    return initWithString(vShaderStream.str(), fShaderStream.str());
}

bool Shader::initWithString(const std::string &vertexCode, const std::string &fragmentCode)
{
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar * fShaderCode = fragmentCode.c_str();
    // Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    // Shader Program
    _data->program = glCreateProgram();
    glAttachShader(_data->program, vertex);
    glAttachShader(_data->program, fragment);
    glLinkProgram(_data->program);
    // Print linking errors if any
    glGetProgramiv(_data->program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_data->program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void Shader::use()
{
    assert(_data->program != 0);
    glUseProgram(_data->program);
}

int Shader::object() const
{
    return (int)_data->program;
}

int Shader::getUniformLocation(const std::string & name)
{
    return (int)glGetUniformLocation((GLuint)_data->program, name.c_str());
}

void Shader::setUniformValue(const std::string & uniformName, int value)
{
    glUniform1i(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), value);
}

void Shader::setUniformValue(const std::string & uniformName, float value)
{
    glUniform1f(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), value);
}

void Shader::setUniformValue(const std::string & uniformName, const glm::Vec2 & value)
{
    glUniform2f(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), value.x, value.y);
}

void Shader::setUniformValue(const std::string & uniformName, const glm::Vec3 & value)
{
    glUniform3f(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), value.x, value.y, value.z);
}

void Shader::setUniformValue(const std::string & uniformName, const glm::Vec4 & value)
{
    glUniform4f(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setUniformValuePointer(const std::string & uniformName, ssize_t size, const float * pointer)
{
    glUniform1fv(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), size, pointer);
}

void Shader::setUniformValuePointer(const std::string & uniformName, ssize_t size, const glm::Vec2 * pointer)
{
    glUniform2fv(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), size, glm::value_ptr(*pointer));
}

void Shader::setUniformValuePointer(const std::string & uniformName, ssize_t size, const glm::Vec3 * pointer)
{
    glUniform3fv(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), size, glm::value_ptr(*pointer));
}

void Shader::setUniformValuePointer(const std::string & uniformName, ssize_t size, const glm::Vec4 * pointer)
{
    glUniform4fv(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), size, glm::value_ptr(*pointer));
}

void Shader::setUniformValue(const std::string & uniformName, const glm::Mat4 & value)
{
    glUniformMatrix4fv(glGetUniformLocation((GLuint)_data->program, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniformValue(const std::string & uniformName, Texture * texture)
{
    setUniformValue(uniformName.c_str(), (int)0);
    texture->active();
}

