#include "CameraController.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "GLFW/glfw3.h"
#include "InputSystem.h"


void CameraController::Update(float deltaTime)
{
    glm::vec3 posDelta = {};
    if (Input::GetKey(GLFW_KEY_W, GLFW_PRESS))
        posDelta = cameraSpeed * camera->GetForward();
    if (Input::GetKey(GLFW_KEY_S, GLFW_PRESS))
        posDelta = -cameraSpeed * camera->GetForward();
    if (Input::GetKey(GLFW_KEY_A, GLFW_PRESS))
        posDelta = -camera->GetRight() * cameraSpeed;
    if (Input::GetKey(GLFW_KEY_D, GLFW_PRESS))
        posDelta = camera->GetRight() * cameraSpeed;
    posDelta *= deltaTime;

    camera->position += posDelta;
}