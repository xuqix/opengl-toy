#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include <string>
#include <functional>

#include "InputEvent.h"
#include "mathlib.h"

class GLWindow
{
public:
    GLWindow(int width, int height, const std::string &title);

    ~GLWindow();

    bool windowShouldClose() const;

    void swapBuffers();

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
    struct PrivateData;

    PrivateData *_data;

    friend class GLFWEventHandler;
};

#endif
