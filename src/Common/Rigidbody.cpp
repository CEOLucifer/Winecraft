#include "Common/Rigidbody.h"
#include "Core/Branch.h"
#include "TimeSystem.h"
#include "Block/BlockSystem.h"

void Rigidbody::Update()
{
    updatePhysics();
}

void Rigidbody::updatePhysics()
{
    Sp<Branch> parent = GetParent().lock();


    // 速度
    velocity.y += g * Time::GetDeltaTime();

    // 垂直方块碰撞检测
    vec3 pos = parent->GetPosition();
    i32vec3 bwc = parent->GetPosition();
    auto block = BlockSystem::Instance()->GetBlock(bwc);
    if (block && (*block).id != 0)
    {
        velocity.y = 0;
        parent->SetPosition({pos.x, bwc.y + 1, pos.z});
    }

    // 位移
    vec3 s = velocity * Time::GetDeltaTime();
    parent->SetPosition(parent->GetPosition() + s);
}