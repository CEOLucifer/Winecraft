#include "UI/Control.h"
#include "Core/Branch.h"
#include "Debug/Debug.h"

glm::vec2 Control::GetSize()
{
    // 宽高就是Scale的xy分量
    Sp<Branch> parent = GetParent().lock();
    if (parent)
    {
        return parent->Scale;
    }
    Debug::LogError("Control has no parent.");
    return {0, 0};
}

void Control::SetSize(glm::vec2 value)
{
    Sp<Branch> parent = GetParent().lock();
    if (parent)
    {
        parent->Scale.x = value.x;
        parent->Scale.y = value.y;
    }
}

glm::vec2 Control::GetPos()
{
    Sp<Branch> parent = GetParent().lock();
    return {parent->Position.x, parent->Position.y};
}
