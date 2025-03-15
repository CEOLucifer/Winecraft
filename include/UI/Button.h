#pragma once

#include "Control.h"
#include <functional>

class Button : public Control
{
private:
    std::function<void()> onClick;
    std::function<void()> onHovering;
    std::function<void()> onDown;
    std::function<void()> onUp;

public:
    void OnClick(std::function<void()> value)
    {
        onClick = value;
    }

    void TriggerOnClick()
    {
        if (onClick)
            onClick();
    }

    void OnHovering(std::function<void()> value)
    {
        onHovering = value;
    }

    void TriggerOnHovering()
    {
        if (onHovering)
            onHovering();
    }

    void OnDown(std::function<void()> value)
    {
        onDown = value;
    }

    void TriggerOnDown()
    {
        if (onDown)
            onDown();
    }

    void OnUp(std::function<void()> value)
    {
        onUp = value;
    }

    void TriggerOnUp()
    {
        if (onUp)
            onUp();
    }

    void Update() override;
};