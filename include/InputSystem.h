#pragma once

#include "GLFW/glfw3.h"
#include "Input/MouseButton.hpp"
#include "glm/glm.hpp"
#include "EMouseButton.hpp"
#include "EMouseAction.hpp"

class GLFWwindow;

/// @brief 输入系统。
///
class Input
{
    friend class App;

private:
    static GLFWwindow* window;
    static glm::vec2 lastCursorPos;
    static glm::vec2 curCursorPos;
    static glm::vec2 deltaCursorPos;

    static MouseButton mouseButtons[3];

public:
    static bool GetKey(int key, int type)
    {
        return glfwGetKey(window, key) == type;
    }

    static glm::vec2 GetCursorPos()
    { return curCursorPos; }

    static glm::vec2 GetCursorDelta();

    static bool GetMouse(EMouseButton button, EMouseAction action);

    static void ResetMouseActions();

private:
    static void init(GLFWwindow* value);

    static void record()
    {
        lastCursorPos = curCursorPos;
        curCursorPos = reallyGetCursorPos();
        deltaCursorPos = curCursorPos - lastCursorPos;
    }

    static glm::vec2 reallyGetCursorPos()
    {
        double x;
        double y;

        int w;
        int h;
        glfwGetWindowSize(window, &w, &h);
        glfwGetCursorPos(window, &x, &y);

        return {x, h - y};
    }
};