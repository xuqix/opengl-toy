#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include <string>
#include <functional>

#include "InputEvent.h"
#include "mathlib.h"

class GLWindow
{
public:
    GLWindow();

    GLWindow(int width, int height, const std::string &title);

    ~GLWindow();

    bool shouldClose() const;

    void swapBuffers();

    void clear(const glm::Vec4 &color = glm::Vec4(1.0f,1.0f,1.0f,1.0f));

    void pollEvents();

    void setCursorVisible(bool isVisible);

    void setResizable(bool isResizable);

    void setKeyEventCallback(const std::function<void(GLWindow*, KeyEvent)> &cb);

    void setMouseCallback(const std::function<void(GLWindow*, MouseEvent)> &cb);

    void setScrollCallback(const std::function<void(GLWindow*, ScrollEvent)> &cb);

    bool getKeyState(KeyEvent::KeyCode code) const;

    float getTime() const;

    // internal window handle
    void* windowId() const;

private:
    GLWindow(const GLWindow&) = delete;
    GLWindow& operator=(const GLWindow&) = delete;

    struct PrivateData;
    PrivateData *_data;

    friend class GLFWEventHandler;
};

#endif
