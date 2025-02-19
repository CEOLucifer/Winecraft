#include "CameraController.h"
#include "Camera.h"
#include "GLFW/glfw3.h"
#include "InputSystem.h"
#include <algorithm>
#include "Debug/Debug.h"

using namespace std;

void CameraController::OnUpdate(float deltaTime)
{
    glm::vec3 posDelta = {};
    if (Input::GetKey(GLFW_KEY_W, GLFW_PRESS))
        posDelta += cameraSpeed * camera->GetForward();
    if (Input::GetKey(GLFW_KEY_S, GLFW_PRESS))
        posDelta += -cameraSpeed * camera->GetForward();
    if (Input::GetKey(GLFW_KEY_A, GLFW_PRESS))
        posDelta += -camera->GetRight() * cameraSpeed;
    if (Input::GetKey(GLFW_KEY_D, GLFW_PRESS))
        posDelta += camera->GetRight() * cameraSpeed;
    posDelta *= deltaTime;

    if (Input::GetKey(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS))
    {
        posDelta *= 3;
    }

    camera->position += posDelta;


    glm::vec2 cursorDelta = Input::GetCursorDelta() * cursorSpeed * deltaTime;
    camera->rotation.x =
        clamp(camera->rotation.x + cursorDelta.y, -90.0f, 90.0f);
    camera->rotation.y = camera->rotation.y - cursorDelta.x;
}