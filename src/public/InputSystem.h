#pragma once

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

class GLFWwindow;

/// @brief 输入系统。
///
class Input
{
private:
    static GLFWwindow* window;
    static glm::vec2 lastCursorPos;

public:
    static void SetWindow(GLFWwindow* value) { window = value; }

    static bool GetKey(int key, int type)
    {
        return glfwGetKey(window, key) == type;
    }

    static void SetLastCursorPos(glm::vec2 value) { lastCursorPos = value; }

    static glm::vec2 GetCursorPos()
    {
        double x;
        double y;

        int w;
        int h;
        glfwGetWindowSize(window, &w, &h);
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2((float)x, h - (float)y);
    }

    static glm::vec2 GetCursorDelta() { return GetCursorPos() - lastCursorPos; }
};