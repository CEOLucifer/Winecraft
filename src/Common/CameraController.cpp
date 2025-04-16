#include "Common/CameraController.h"
#include "Render/Camera.h"
#include "GLFW/glfw3.h"
#include "InputSystem.h"
#include <algorithm>
#include "TimeSystem.h"
#include "Core/Branch.h"
#include "Debug/Debug.h"

using namespace std;

void CameraController::Update()
{
    if (!camera)
    {
        return;
    }

    auto parent = camera->GetParent().lock();

    // 移动
    if (isEnableMove)
    {
        glm::vec3 posDelta = {0, 0, 0};

        if (Input::GetKey(GLFW_KEY_W, GLFW_PRESS))
            posDelta += cameraSpeed * parent->GetForward();
        if (Input::GetKey(GLFW_KEY_S, GLFW_PRESS))
            posDelta += -cameraSpeed * parent->GetForward();
        if (Input::GetKey(GLFW_KEY_A, GLFW_PRESS))
            posDelta += -parent->GetRight() * cameraSpeed;
        if (Input::GetKey(GLFW_KEY_D, GLFW_PRESS))
            posDelta += parent->GetRight() * cameraSpeed;
        posDelta *= Time::GetDeltaTime();

        if (Input::GetKey(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS))
        {
            posDelta *= 3;
        }

        parent->Position += posDelta;
    }



    // 旋转
    glm::vec2 cursorDelta =
            Input::GetCursorDelta() * cursorSpeed * Time::GetDeltaTime();
    parent->Rotation.x =
            clamp(parent->Rotation.x - cursorDelta.y, -90.0f, 90.0f);
    parent->Rotation.y = parent->Rotation.y - cursorDelta.x;


    // 滚轮

    // 测试
//    Debug::Log(Input::GetCursorPos());
}

void CameraController::OnAdded()
{
    camera = GetParent().lock()->GetChild<Camera>();
}
