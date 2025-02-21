#include "InputSystem.h"

GLFWwindow* Input::window = nullptr;
glm::vec2 Input::deltaCursorPos = {0, 0};
glm::vec2 Input::lastCursorPos = {0, 0};
glm::vec2 Input::curCursorPos = {0, 0};