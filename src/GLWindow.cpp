#include "GLWindow.h"

#include <unordered_map>

#include "GL.h"
#include "DebugHelper.h"
#include "Utils.h"

namespace std{
    template<>
    struct std::hash<KeyEvent::KeyCode>
    {
        std::size_t operator()(const KeyEvent::KeyCode &k) const
        {
            return std::hash<int>()((int)k);
        }
    };
}

static std::unordered_map<int, KeyEvent::KeyCode> g_keycodeMap = {
    /* The unknown key */
    { GLFW_KEY_UNKNOWN         , KeyEvent::KeyCode::KEY_NONE          },

    /* Printable keys */
    { GLFW_KEY_SPACE           , KeyEvent::KeyCode::KEY_SPACE         },
    { GLFW_KEY_APOSTROPHE      , KeyEvent::KeyCode::KEY_APOSTROPHE    },
    { GLFW_KEY_COMMA           , KeyEvent::KeyCode::KEY_COMMA         },
    { GLFW_KEY_MINUS           , KeyEvent::KeyCode::KEY_MINUS         },
    { GLFW_KEY_PERIOD          , KeyEvent::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_SLASH           , KeyEvent::KeyCode::KEY_SLASH         },
    { GLFW_KEY_0               , KeyEvent::KeyCode::KEY_0             },
    { GLFW_KEY_1               , KeyEvent::KeyCode::KEY_1             },
    { GLFW_KEY_2               , KeyEvent::KeyCode::KEY_2             },
    { GLFW_KEY_3               , KeyEvent::KeyCode::KEY_3             },
    { GLFW_KEY_4               , KeyEvent::KeyCode::KEY_4             },
    { GLFW_KEY_5               , KeyEvent::KeyCode::KEY_5             },
    { GLFW_KEY_6               , KeyEvent::KeyCode::KEY_6             },
    { GLFW_KEY_7               , KeyEvent::KeyCode::KEY_7             },
    { GLFW_KEY_8               , KeyEvent::KeyCode::KEY_8             },
    { GLFW_KEY_9               , KeyEvent::KeyCode::KEY_9             },
    { GLFW_KEY_SEMICOLON       , KeyEvent::KeyCode::KEY_SEMICOLON     },
    { GLFW_KEY_EQUAL           , KeyEvent::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_A               , KeyEvent::KeyCode::KEY_A             },
    { GLFW_KEY_B               , KeyEvent::KeyCode::KEY_B             },
    { GLFW_KEY_C               , KeyEvent::KeyCode::KEY_C             },
    { GLFW_KEY_D               , KeyEvent::KeyCode::KEY_D             },
    { GLFW_KEY_E               , KeyEvent::KeyCode::KEY_E             },
    { GLFW_KEY_F               , KeyEvent::KeyCode::KEY_F             },
    { GLFW_KEY_G               , KeyEvent::KeyCode::KEY_G             },
    { GLFW_KEY_H               , KeyEvent::KeyCode::KEY_H             },
    { GLFW_KEY_I               , KeyEvent::KeyCode::KEY_I             },
    { GLFW_KEY_J               , KeyEvent::KeyCode::KEY_J             },
    { GLFW_KEY_K               , KeyEvent::KeyCode::KEY_K             },
    { GLFW_KEY_L               , KeyEvent::KeyCode::KEY_L             },
    { GLFW_KEY_M               , KeyEvent::KeyCode::KEY_M             },
    { GLFW_KEY_N               , KeyEvent::KeyCode::KEY_N             },
    { GLFW_KEY_O               , KeyEvent::KeyCode::KEY_O             },
    { GLFW_KEY_P               , KeyEvent::KeyCode::KEY_P             },
    { GLFW_KEY_Q               , KeyEvent::KeyCode::KEY_Q             },
    { GLFW_KEY_R               , KeyEvent::KeyCode::KEY_R             },
    { GLFW_KEY_S               , KeyEvent::KeyCode::KEY_S             },
    { GLFW_KEY_T               , KeyEvent::KeyCode::KEY_T             },
    { GLFW_KEY_U               , KeyEvent::KeyCode::KEY_U             },
    { GLFW_KEY_V               , KeyEvent::KeyCode::KEY_V             },
    { GLFW_KEY_W               , KeyEvent::KeyCode::KEY_W             },
    { GLFW_KEY_X               , KeyEvent::KeyCode::KEY_X             },
    { GLFW_KEY_Y               , KeyEvent::KeyCode::KEY_Y             },
    { GLFW_KEY_Z               , KeyEvent::KeyCode::KEY_Z             },
    { GLFW_KEY_LEFT_BRACKET    , KeyEvent::KeyCode::KEY_LEFT_BRACKET  },
    { GLFW_KEY_BACKSLASH       , KeyEvent::KeyCode::KEY_BACK_SLASH    },
    { GLFW_KEY_RIGHT_BRACKET   , KeyEvent::KeyCode::KEY_RIGHT_BRACKET },
    { GLFW_KEY_GRAVE_ACCENT    , KeyEvent::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_1         , KeyEvent::KeyCode::KEY_GRAVE         },
    { GLFW_KEY_WORLD_2         , KeyEvent::KeyCode::KEY_NONE          },

    /* Function keys */
    { GLFW_KEY_ESCAPE          , KeyEvent::KeyCode::KEY_ESCAPE        },
    { GLFW_KEY_ENTER           , KeyEvent::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_TAB             , KeyEvent::KeyCode::KEY_TAB           },
    { GLFW_KEY_BACKSPACE       , KeyEvent::KeyCode::KEY_BACKSPACE     },
    { GLFW_KEY_INSERT          , KeyEvent::KeyCode::KEY_INSERT        },
    { GLFW_KEY_DELETE          , KeyEvent::KeyCode::KEY_DELETE        },
    { GLFW_KEY_RIGHT           , KeyEvent::KeyCode::KEY_RIGHT_ARROW   },
    { GLFW_KEY_LEFT            , KeyEvent::KeyCode::KEY_LEFT_ARROW    },
    { GLFW_KEY_DOWN            , KeyEvent::KeyCode::KEY_DOWN_ARROW    },
    { GLFW_KEY_UP              , KeyEvent::KeyCode::KEY_UP_ARROW      },
    { GLFW_KEY_PAGE_UP         , KeyEvent::KeyCode::KEY_KP_PG_UP      },
    { GLFW_KEY_PAGE_DOWN       , KeyEvent::KeyCode::KEY_KP_PG_DOWN    },
    { GLFW_KEY_HOME            , KeyEvent::KeyCode::KEY_KP_HOME       },
    { GLFW_KEY_END             , KeyEvent::KeyCode::KEY_END           },
    { GLFW_KEY_CAPS_LOCK       , KeyEvent::KeyCode::KEY_CAPS_LOCK     },
    { GLFW_KEY_SCROLL_LOCK     , KeyEvent::KeyCode::KEY_SCROLL_LOCK   },
    { GLFW_KEY_NUM_LOCK        , KeyEvent::KeyCode::KEY_NUM_LOCK      },
    { GLFW_KEY_PRINT_SCREEN    , KeyEvent::KeyCode::KEY_PRINT         },
    { GLFW_KEY_PAUSE           , KeyEvent::KeyCode::KEY_PAUSE         },
    { GLFW_KEY_F1              , KeyEvent::KeyCode::KEY_F1            },
    { GLFW_KEY_F2              , KeyEvent::KeyCode::KEY_F2            },
    { GLFW_KEY_F3              , KeyEvent::KeyCode::KEY_F3            },
    { GLFW_KEY_F4              , KeyEvent::KeyCode::KEY_F4            },
    { GLFW_KEY_F5              , KeyEvent::KeyCode::KEY_F5            },
    { GLFW_KEY_F6              , KeyEvent::KeyCode::KEY_F6            },
    { GLFW_KEY_F7              , KeyEvent::KeyCode::KEY_F7            },
    { GLFW_KEY_F8              , KeyEvent::KeyCode::KEY_F8            },
    { GLFW_KEY_F9              , KeyEvent::KeyCode::KEY_F9            },
    { GLFW_KEY_F10             , KeyEvent::KeyCode::KEY_F10           },
    { GLFW_KEY_F11             , KeyEvent::KeyCode::KEY_F11           },
    { GLFW_KEY_F12             , KeyEvent::KeyCode::KEY_F12           },
    { GLFW_KEY_F13             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F14             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F15             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F16             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F17             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F18             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F19             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F20             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F21             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F22             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F23             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F24             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_F25             , KeyEvent::KeyCode::KEY_NONE          },
    { GLFW_KEY_KP_0            , KeyEvent::KeyCode::KEY_0             },
    { GLFW_KEY_KP_1            , KeyEvent::KeyCode::KEY_1             },
    { GLFW_KEY_KP_2            , KeyEvent::KeyCode::KEY_2             },
    { GLFW_KEY_KP_3            , KeyEvent::KeyCode::KEY_3             },
    { GLFW_KEY_KP_4            , KeyEvent::KeyCode::KEY_4             },
    { GLFW_KEY_KP_5            , KeyEvent::KeyCode::KEY_5             },
    { GLFW_KEY_KP_6            , KeyEvent::KeyCode::KEY_6             },
    { GLFW_KEY_KP_7            , KeyEvent::KeyCode::KEY_7             },
    { GLFW_KEY_KP_8            , KeyEvent::KeyCode::KEY_8             },
    { GLFW_KEY_KP_9            , KeyEvent::KeyCode::KEY_9             },
    { GLFW_KEY_KP_DECIMAL      , KeyEvent::KeyCode::KEY_PERIOD        },
    { GLFW_KEY_KP_DIVIDE       , KeyEvent::KeyCode::KEY_KP_DIVIDE     },
    { GLFW_KEY_KP_MULTIPLY     , KeyEvent::KeyCode::KEY_KP_MULTIPLY   },
    { GLFW_KEY_KP_SUBTRACT     , KeyEvent::KeyCode::KEY_KP_MINUS      },
    { GLFW_KEY_KP_ADD          , KeyEvent::KeyCode::KEY_KP_PLUS       },
    { GLFW_KEY_KP_ENTER        , KeyEvent::KeyCode::KEY_KP_ENTER      },
    { GLFW_KEY_KP_EQUAL        , KeyEvent::KeyCode::KEY_EQUAL         },
    { GLFW_KEY_LEFT_SHIFT      , KeyEvent::KeyCode::KEY_LEFT_SHIFT         },
    { GLFW_KEY_LEFT_CONTROL    , KeyEvent::KeyCode::KEY_LEFT_CTRL          },
    { GLFW_KEY_LEFT_ALT        , KeyEvent::KeyCode::KEY_LEFT_ALT           },
    { GLFW_KEY_LEFT_SUPER      , KeyEvent::KeyCode::KEY_HYPER         },
    { GLFW_KEY_RIGHT_SHIFT     , KeyEvent::KeyCode::KEY_RIGHT_SHIFT         },
    { GLFW_KEY_RIGHT_CONTROL   , KeyEvent::KeyCode::KEY_RIGHT_CTRL          },
    { GLFW_KEY_RIGHT_ALT       , KeyEvent::KeyCode::KEY_RIGHT_ALT           },
    { GLFW_KEY_RIGHT_SUPER     , KeyEvent::KeyCode::KEY_HYPER         },
    { GLFW_KEY_MENU            , KeyEvent::KeyCode::KEY_MENU          },
    { GLFW_KEY_LAST            , KeyEvent::KeyCode::KEY_NONE          }
};

struct GLWindow::PrivateData
{
    std::string title = "";
    glm::Rect rect = {0,0,0,0};

    bool isVisible = true;
    bool isResizable = true;

    GLFWwindow *window = nullptr;

    std::unordered_map<KeyEvent::KeyCode, bool> keyStates;

    std::function<void(GLWindow*,KeyEvent)> onKeyCallback = nullptr;

    std::function<void(GLWindow*,MouseEvent)> onMouseCallback = nullptr;

    std::function<void(GLWindow*,ScrollEvent)> onScrollCallback = nullptr;
};

class GLFWEventHandler
{
public:
    static void onKeyCallback(GLFWwindow*, int key, int scancode, int action, int mode)
    {
        UNUSED_PARAM(scancode);
        UNUSED_PARAM(mode);
        if(!_view) return;

        if(_view->_data->onKeyCallback)
        {
            if(GLFW_REPEAT != action)
            {
                auto keycode = g_keycodeMap[key];
                bool isPressed = GLFW_PRESS == action;
                _view->_data->keyStates[keycode] = isPressed;
                _view->_data->onKeyCallback(_view, KeyEvent(keycode, isPressed));
            }
        }
    }

    static void onMouseCallback(GLFWwindow*, double xpos, double ypos)
    {
        if(_view) return;

        if(_view->_data->onMouseCallback)
        {
            _view->_data->onMouseCallback(_view, MouseEvent(xpos, ypos));
        }
    }

    static void onScrollCallback(GLFWwindow*, double xoffset, double yoffset)
    {
        if(_view)
        {
            if(_view->_data->onScrollCallback)
            {
                _view->_data->onScrollCallback(_view, ScrollEvent(xoffset, yoffset));
            }
        }
    }

    static void setGLWindow(GLWindow *window) { _view = window; }

private:
    static GLWindow *_view;
};
GLWindow *GLFWEventHandler::_view = nullptr;

GLWindow::GLWindow(int width, int height, const std::string & title):_data(new PrivateData())
{
    _data->title = title;
    _data->rect = glm::Rect(0, 0, width, height);
    if(glfwInit())
    {
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        _data->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if(!_data->window) return;

        GLFWEventHandler::setGLWindow(this);

        glfwMakeContextCurrent(_data->window);

        int w, h;
        glfwGetFramebufferSize(_data->window, &w, &h);
        glViewport(0, 0, w, h);
    }
}

GLWindow::~GLWindow()
{
    delete _data;
}

bool GLWindow::windowShouldClose() const
{
    if (_data->window)
        return glfwWindowShouldClose(_data->window);
    return true;
}

void GLWindow::swapBuffers()
{
    if(!_data->window) return;

    glfwSwapBuffers(_data->window);
}

void GLWindow::setCursorVisible(bool isVisible)
{
    if(!_data->window) return;

    glfwSetInputMode(_data->window, GLFW_CURSOR, isVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void GLWindow::setResizable(bool isResizable)
{
    glfwWindowHint(GLFW_RESIZABLE, isResizable ? GL_TRUE : GL_FALSE);
}

void GLWindow::setKeyEventCallback(const std::function<void(GLWindow*,KeyEvent)> & cb)
{
    if(!_data->window) return;

    _data->onKeyCallback = cb;
    glfwSetKeyCallback(_data->window, GLFWEventHandler::onKeyCallback);
}

void GLWindow::setMouseCallback(const std::function<void(GLWindow*,MouseEvent)> & cb)
{
    if(!_data->window) return;

    _data->onMouseCallback = cb;
    glfwSetCursorPosCallback(_data->window, GLFWEventHandler::onMouseCallback);
}

void GLWindow::setScrollCallback(const std::function<void(GLWindow*,ScrollEvent)> & cb)
{
    if(!_data->window) return;

    _data->onScrollCallback = cb;
    glfwSetScrollCallback(_data->window, GLFWEventHandler::onScrollCallback);
}

bool GLWindow::getKeyState(KeyEvent::KeyCode code) const
{
    return _data->keyStates[code];
}

float GLWindow::getTime() const
{
    return glfwGetTime();
}

void* GLWindow::windowId() const
{
    return (void*)_data->window;
}

