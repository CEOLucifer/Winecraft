#include "Creature/Player.h"
#include "Common/Rigidbody.h"
#include "Render/Camera.h"
#include "Common/CameraController.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "Block/LatticeRenderCenter.h"
#include "Game/GameSystem.h"

void Player::Awake()
{
    rigidbody = AddNode<Rigidbody>();
    cameraBra = AddNode<Branch>("cameraBra");
    auto camera = cameraBra->AddNode<Camera>();
    auto cameraController = cameraBra->AddNode<CameraController>();
    cameraController->SetIsEnableMove(false);
    cameraBra->SetPosition({0, 1.8, 0});
    cameraBra->AddNode<LatticeRenderCenter>();

    SetPosition({0, 1, 0});

    GameSystem::GetInstance().SetPlayer(CastTo<Player>());
}

void Player::Update()
{
    // 输入控制

    glm::vec3 posDelta = {0, 0, 0};

    if (Input::GetKey(GLFW_KEY_W, GLFW_PRESS))
    {
        vec3 dir = cameraBra->GetForward();
        dir.y = 0;
        dir = glm::normalize(dir);
        posDelta += walkSpeed * dir;
    }
    if (Input::GetKey(GLFW_KEY_S, GLFW_PRESS))
    {
        vec3 dir = cameraBra->GetForward();
        dir.y = 0;
        dir = glm::normalize(dir);
        posDelta += -walkSpeed * dir;
    }
    if (Input::GetKey(GLFW_KEY_A, GLFW_PRESS))
    {
        vec3 dir = cameraBra->GetRight();
        dir.y = 0;
        dir = glm::normalize(dir);
        posDelta += -dir * walkSpeed;
    }
    if (Input::GetKey(GLFW_KEY_D, GLFW_PRESS))
    {
        vec3 dir = cameraBra->GetRight();
        dir.y = 0;
        dir = glm::normalize(dir);
        posDelta += dir * walkSpeed;
    }
    posDelta *= Time::GetDeltaTime();

    if (Input::GetKey(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS))
    {
        posDelta *= 1.8;
    }

    SetPosition(GetPosition() + posDelta);

    // 跳跃
    if (Input::GetKey(GLFW_KEY_SPACE, GLFW_PRESS))
    {
        vec3 velocity = rigidbody->GetVelocity();
        velocity.y = 8;
        rigidbody->SetVelocity(velocity);
    }


    // 测试
    if (Input::GetKey(GLFW_KEY_P, GLFW_PRESS))
    {
        SetPosition({53, 80, 53});
    }
}