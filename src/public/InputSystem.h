#pragma once

#include "GLFW/glfw3.h"

class GLFWwindow;

/// @brief 输入系统。
/// 
class Input
{
private:
    static GLFWwindow* window;

public:
    static void SetWindow(GLFWwindow* value) { window = value; }

    static bool GetKey(int key, int type)
    {
        return glfwGetKey(window, key) == type;
    }
};