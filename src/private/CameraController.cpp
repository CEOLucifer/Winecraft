#include "CameraController.h"
#include "Camera.h"
#include "Core/GameObject.h"
#include "GLFW/glfw3.h"
#include "InputSystem.h"
#include <algorithm>
#include "TimeSystem.h"

using namespace std;

void CameraController::Update()
{
    glm::vec3 posDelta = {};

    Sp<GameObject> gameObject = camera->GetGameObject();

    if (Input::GetKey(GLFW_KEY_W, GLFW_PRESS))
        posDelta += cameraSpeed * gameObject->GetForward();
    if (Input::GetKey(GLFW_KEY_S, GLFW_PRESS))
        posDelta += -cameraSpeed * gameObject->GetForward();
    if (Input::GetKey(GLFW_KEY_A, GLFW_PRESS))
        posDelta += -gameObject->GetRight() * cameraSpeed;
    if (Input::GetKey(GLFW_KEY_D, GLFW_PRESS))
        posDelta += gameObject->GetRight() * cameraSpeed;
    posDelta *= Time::GetDeltaTime();

    if (Input::GetKey(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS))
    {
        posDelta *= 3;
    }

    gameObject->Position += posDelta;

    // Debug::Log(1 / deltaTime);


    glm::vec2 cursorDelta =
        Input::GetCursorDelta() * cursorSpeed * Time::GetDeltaTime();
    gameObject->Rotation.x =
        clamp(gameObject->Rotation.x + cursorDelta.y, -90.0f, 90.0f);
    gameObject->Rotation.y = gameObject->Rotation.y - cursorDelta.x;
}