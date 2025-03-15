#include "UI/Button.h"
#include "InputSystem.h"

void Button::Update()
{
    // 检测事件是否应该触发
    glm::vec2 pos = GetPos();
    glm::vec2 size = GetSize();
    glm::vec2 cursorPos = Input::GetCursorPos();

    if (pos.x - size.x / 2 < cursorPos.x &&
        cursorPos.x < pos.x + size.x / 2 &&
        pos.y - size.y / 2 < cursorPos.y &&
        cursorPos.y < pos.y + size.y / 2)
    {
        TriggerOnHovering();

        if (Input::GetMouse(EMouseButton::Left, EMouseAction::Down))
        {
            TriggerOnDown();
        }
        else if(Input::GetMouse(EMouseButton::Left, EMouseAction::Up))
        {
            TriggerOnUp();
        }
    }
}