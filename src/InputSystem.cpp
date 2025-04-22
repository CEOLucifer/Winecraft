#include "InputSystem.h"
#include "EMouseAction.hpp"
#include "TimeSystem.h"
#include "Debug/Debug.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include "Std/Basic.h"


GLFWwindow* Input::window = nullptr;
glm::vec2 Input::deltaCursorPos = {0, 0};
glm::vec2 Input::lastCursorPos = {0, 0};
glm::vec2 Input::curCursorPos = {0, 0};
MouseButton Input::mouseButtons[3] = {};
Signal<void(KeySignal)> Input::keySignal = {};

glm::vec2 Input::GetCursorDelta()
{
    return deltaCursorPos / Time::GetDeltaTime();
}

bool Input::GetMouse(EMouseButton button, EMouseAction action)
{
    return mouseButtons[(i32)button].action == action;
}

void Input::init(GLFWwindow* value)
{
    window = value;
    lastCursorPos = curCursorPos = reallyGetCursorPos();

    // 鼠标输入
    glfwSetMouseButtonCallback(
        window, [](GLFWwindow* window, int button, int action, int mods)
        { mouseButtons[button].action = (EMouseAction)action; });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                  int action, int mods)
                       { onKeyCallback(window, key, scancode, action, mods); });
}

void Input::ResetMouseActions()
{
    for (i32 i = 0; i < 3; ++i)
    {
        mouseButtons[i].action = EMouseAction::None;
    }
}

void Input::onKeyCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mods)
{
    if (action == GLFW_REPEAT)
    {
        return;
    }
    keySignal({key, action});
}