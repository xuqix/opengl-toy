#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <OpenGL/gl3.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

struct Shader::PrivateData
{
    GLuint program = 0;
};

Shader::Shader():_data(new Shader::PrivateData()) {}

Shader::~Shader()
{
    delete _data;
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
