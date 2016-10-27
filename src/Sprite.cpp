#include "Sprite.h"

#include "GL.h"
#include "Image.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "Utils.h"

using namespace glm;
using namespace Utils;

static GLuint indices[] =
{
    0, 1, 2,
    1, 2, 3
};

struct Sprite::PrivateData
{
    Vec3 position = Vec3(0, 0, 0);
    Vec3 rotation = Vec3(0, 0, 0);

    Image   *image = nullptr;
    Texture *texture = nullptr;
    Shader  *shader = nullptr;

    // for gl
    GLuint vao, vbo, ebo;
};

Sprite::Sprite():_data(new PrivateData())
{

}

Sprite::Sprite(const std::string &path):_data(new PrivateData())
{
    Image *image = new Image(path);
    if(!image->valid()) return;
    _data->image = image;

    _data->texture = new Texture(image);

    _data->shader = new Shader();
    _data->shader->initWithBuiltin(Shader::BuiltinShader::SHADER_POSITION_COLOR_TEXTURE);

    GLfloat vert[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, //bot left
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f, //bot right
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, //top left
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, //top right
    };

    glGenVertexArrays(1, &_data->vao);
    glBindVertexArray(_data->vao);

    glGenBuffers(1, &_data->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _data->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    glGenBuffers(1, &_data->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _data->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Sprite::~Sprite()
{
    delete _data;
}

const glm::Vec3 & Sprite::getPosition() const
{
    return _data->position;
}

void Sprite::setPosition(const glm::Vec3 & pos)
{
    _data->position = pos;
}

const glm::Vec3 & Sprite::getRotation() const
{
    return _data->rotation;
}

void Sprite::setRotation(const glm::Vec3 & rotation)
{
    _data->rotation = rotation;
}

Image* Sprite::getImage()
{
    return _data->image;
}

Texture* Sprite::getTexture()
{
    return _data->texture;
}

Shader* Sprite::getShader()
{
    return _data->shader;
}

void Sprite::draw()
{
    _data->texture->active();

    _data->shader->use();
    _data->shader->setUniformValue(Shader::UNIFORM_TEXTURE0, _data->texture);

    auto camera = Camera::getCurrent();
    glm::mat4 model, view, projection;
    model = glm::translate(model, _data->position);
    //todo: rotation
    //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 0, 1));
    _data->shader->setUniformValue(Shader::UNIFORM_M_MATRIX, model);

    view = camera->getViewMatrix();
    _data->shader->setUniformValue(Shader::UNIFORM_V_MATRIX, view);

    projection = camera->getProjectionMatrix();
    _data->shader->setUniformValue(Shader::UNIFORM_P_MATRIX, projection);

    glBindVertexArray(_data->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

