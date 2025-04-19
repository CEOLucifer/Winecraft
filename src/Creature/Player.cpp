#include "Creature/Player.h"
#include "Common/Rigidbody.h"
#include "Render/Camera.h"
#include "Common/CameraController.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "Block/LatticeRenderCenter.h"
#include "Game/GameSystem.h"
#include "Block/BlockSystem.h"
#include "Mathf.h"
#include "Debug/Debug.h"
#include <cmath>

void Player::Awake()
{
    rigidbody = AddNode<Rigidbody>();
    cameraBra = AddNode<Branch>("cameraBra");
    auto camera = cameraBra->AddNode<Camera>();
    auto cameraController = cameraBra->AddNode<CameraController>();
    cameraController->SetIsEnableMove(false);
    cameraBra->SetPosition({0, 1.8, 0});
    cameraBra->AddNode<LatticeRenderCenter>();

    GameSystem::GetInstance().SetPlayer(CastTo<Player>());
}

void Player::Update()
{
    // 输入控制

    // 移动
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

    // 方块破坏
    if (Input::GetMouse(EMouseButton::Left, EMouseAction::Down))
    {
        auto info = GetStaredBlock();
        if (info.block)
        {
            BlockSystem::Instance()->SetBlock(0, info.bwc);
        }
    }

    // 方块放置
    if (Input::GetMouse(EMouseButton::Right, EMouseAction::Down))
    {
        auto cor = GetStaredEmptyBlock();
        if (cor)
        {
            BlockSystem::Instance()->SetBlock(4, *cor);
        }
    }


    // 测试
    if (Input::GetKey(GLFW_KEY_P, GLFW_PRESS))
    {
        SetPosition({53, 80, 53});
    }
}

StaredBlockInfo Player::GetStaredBlock()
{
    StaredBlockInfo res;
    vec3 cameraForward = cameraBra->GetForward();
    vec3 cameraCor = cameraBra->GetPosition();
    f32 x0 = cameraCor.x;
    f32 y0 = cameraCor.y;
    f32 z0 = cameraCor.z;
    f32 m = cameraForward.x;
    f32 n = cameraForward.y;
    f32 p = cameraForward.z;

    vec3 cpt = cameraCor;

    while (true)
    {
        // 利用对称式方程
        vec3 pt[3];
        pt[0].x = cameraForward.x >= 0 ? floor(cpt.x + 1) : ceil(cpt.x - 1);
        pt[0].y = (pt[0].x - x0) / m * n + y0;
        pt[0].z = (pt[0].x - x0) / m * p + z0;

        pt[1].y = cameraForward.y >= 0 ? floor(cpt.y + 1) : ceil(cpt.y - 1);
        pt[1].x = (pt[1].y - y0) / n * m + x0;
        pt[1].z = (pt[1].y - y0) / n * p + z0;

        pt[2].z = cameraForward.z >= 0 ? floor(cpt.z + 1) : ceil(cpt.z - 1);
        pt[2].x = (pt[2].z - z0) / p * m + x0;
        pt[2].y = (pt[2].z - z0) / p * n + y0;

        f32 dis[3];
        dis[0] = glm::distance(cameraCor, pt[0]);
        dis[1] = glm::distance(cameraCor, pt[1]);
        dis[2] = glm::distance(cameraCor, pt[2]);

        // 求最小距离
        i32 minInd = 0;
        if (dis[1] < dis[minInd])
            minInd = 1;
        if (dis[2] < dis[minInd])
            minInd = 2;

        // 射程之内没有方块
        if (dis[minInd] > reachBlockDistance)
        {
            break;
        }

        // 判断方块
        i32vec3 bwc;
        if (minInd == 0)
        {
            bwc = {cameraForward.x >= 0 ? round(pt[0].x - 1) : round(pt[0].x),
                   floor(pt[0].y), floor(pt[0].z)};
        }
        else if (minInd == 1)
        {
            bwc = {floor(pt[1].x),
                   cameraForward.y >= 0 ? round(pt[1].y - 1) : round(pt[1].y),
                   floor(pt[1].z)};
        }
        else
        {
            bwc = {floor(pt[2].x), floor(pt[2].y),
                   cameraForward.z >= 0 ? round(pt[2].z - 1) : round(pt[2].z)};
        }

        res.block = BlockSystem::Instance()->GetBlock(bwc);
        if (res.block && (*res.block) != 0)
        {
            res.bwc = bwc;
            break;
        }

        cpt = pt[minInd];
    }

    return res;
}

Opt<i32vec3> Player::GetStaredEmptyBlock()
{

    // 基本上和GetStaredBlock一样

    Opt<i32vec3> res;
    vec3 cameraForward = cameraBra->GetForward();
    vec3 cameraCor = cameraBra->GetPosition();
    f32 x0 = cameraCor.x;
    f32 y0 = cameraCor.y;
    f32 z0 = cameraCor.z;
    f32 m = cameraForward.x;
    f32 n = cameraForward.y;
    f32 p = cameraForward.z;

    vec3 cpt = cameraCor;
    i32vec3 lastEmptyBlock = {floor(cameraCor.x), floor(cameraCor.y),
                              floor(cameraCor.z)};

    while (true)
    {
        // 利用对称式方程
        vec3 pt[3];
        pt[0].x = cameraForward.x >= 0 ? floor(cpt.x + 1) : ceil(cpt.x - 1);
        pt[0].y = (pt[0].x - x0) / m * n + y0;
        pt[0].z = (pt[0].x - x0) / m * p + z0;

        pt[1].y = cameraForward.y >= 0 ? floor(cpt.y + 1) : ceil(cpt.y - 1);
        pt[1].x = (pt[1].y - y0) / n * m + x0;
        pt[1].z = (pt[1].y - y0) / n * p + z0;

        pt[2].z = cameraForward.z >= 0 ? floor(cpt.z + 1) : ceil(cpt.z - 1);
        pt[2].x = (pt[2].z - z0) / p * m + x0;
        pt[2].y = (pt[2].z - z0) / p * n + y0;

        f32 dis[3];
        dis[0] = glm::distance(cameraCor, pt[0]);
        dis[1] = glm::distance(cameraCor, pt[1]);
        dis[2] = glm::distance(cameraCor, pt[2]);

        // 求最小距离
        i32 minInd = 0;
        if (dis[1] < dis[minInd])
            minInd = 1;
        if (dis[2] < dis[minInd])
            minInd = 2;

        // 射程之内没有方块
        if (dis[minInd] > reachBlockDistance)
        {
            break;
        }

        // 判断方块
        i32vec3 bwc;
        if (minInd == 0)
        {
            bwc = {cameraForward.x >= 0 ? round(pt[0].x - 1) : round(pt[0].x),
                   floor(pt[0].y), floor(pt[0].z)};
        }
        else if (minInd == 1)
        {
            bwc = {floor(pt[1].x),
                   cameraForward.y >= 0 ? round(pt[1].y - 1) : round(pt[1].y),
                   floor(pt[1].z)};
        }
        else
        {
            bwc = {floor(pt[2].x), floor(pt[2].y),
                   cameraForward.z >= 0 ? round(pt[2].z - 1) : round(pt[2].z)};
        }

        // 这里与GetStaredBlock不一样
        auto block = BlockSystem::Instance()->GetBlock(bwc);
        if (block && *block != 0)
        {
            res = lastEmptyBlock;
            break;
        }

        cpt = pt[minInd];
        lastEmptyBlock = bwc;
    }

    return res;
}