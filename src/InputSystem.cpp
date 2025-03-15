#include "InputSystem.h"
#include "TimeSystem.h"
#include "Debug/Debug.h"


GLFWwindow* Input::window = nullptr;
glm::vec2 Input::deltaCursorPos = {0, 0};
glm::vec2 Input::lastCursorPos = {0, 0};
glm::vec2 Input::curCursorPos = {0, 0};

EMouseAction Input::leftAction = EMouseAction::None;
EMouseAction Input::middleAction = EMouseAction::None;
EMouseAction Input::rightAction = EMouseAction::None;

glm::vec2 Input::GetCursorDelta()
{
    return deltaCursorPos / Time::GetDeltaTime();
}

bool Input::GetMouse(EMouseButton button, EMouseAction action)
{
    EMouseAction& actionRef = leftAction;
    if (button == EMouseButton::Middle)
    {
        actionRef = middleAction;
    }
    else if (button == EMouseButton::Right)
    {
        actionRef = rightAction;
    }

    return actionRef == action;
}

void Input::init(GLFWwindow* value)
{
    window = value;
    lastCursorPos = curCursorPos = reallyGetCursorPos();

    // 鼠标输入
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
        EMouseAction& actionRef = leftAction;

        if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        {
            actionRef = middleAction;
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            actionRef = rightAction;
        }

        if (action == GLFW_PRESS)
        {
            actionRef = EMouseAction::Down;
        }
        else if (action == GLFW_RELEASE)
        {
            actionRef = EMouseAction::Up;
        }
    });
}

void Input::ResetMouseActions()
{
    leftAction = EMouseAction::None;
    middleAction = EMouseAction::None;
    rightAction = EMouseAction::None;
}
