#include <iostream>

#include "GL.h"
#include "SOIL.h"
#include "mathlib.h"

#include "DebugHelper.h"

#include "GLWindow.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Image.h"
#include "Utils.h"
#include "Sprite.h"

using namespace std;
using namespace Utils;

int main()
{
    int width = 480, height = 300;

    GLWindow window(width, height, "my glwindow");

    Shader shader;
    //shader.initWithBuiltin(Shader::BuiltinShader::SHADER_POSITION_COLOR_TEXTURE_NO_MVP);
    shader.initWithBuiltin(Shader::BuiltinShader::SHADER_POSITION_COLOR_TEXTURE);

    Image img("resource/pic1.png");
    if(!img.valid()) return 0;
    Texture tex(&img);

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    GLfloat vert[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, //bot left
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f, //bot right
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, //top left
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, //top right
    };

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    float amendW=0, amendS=0, amendA=0, amendD=0;
    window.setKeyEventCallback([&](GLWindow *win, KeyEvent e)mutable{
        switch(e.keyCode)
        {
            case KeyEvent::KeyCode::KEY_W:
                break;
            case KeyEvent::KeyCode::KEY_S:
                break;
            case KeyEvent::KeyCode::KEY_A:
                break;
            case KeyEvent::KeyCode::KEY_D:
                break;
        }
    });

    float amendX = 0.0f, amendY = 0.0f, speed = 0.01f;
    Camera camera(glm::Vec3(0, 0, 2.0f));
    camera.setPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    Sprite *sprite = new Sprite("resource/pic2.png");
    while(!window.shouldClose())
    {
        if(window.getKeyState(KeyEvent::KeyCode::KEY_W))
            amendY += speed;
        else if(window.getKeyState(KeyEvent::KeyCode::KEY_S))
            amendY -= speed;
        else if(window.getKeyState(KeyEvent::KeyCode::KEY_A))
            amendX -= speed;
        else if(window.getKeyState(KeyEvent::KeyCode::KEY_D))
            amendX += speed;

        window.clear();

        sprite->setPosition(glm::vec3(amendX, amendY, 0));
        sprite->draw();

        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}

