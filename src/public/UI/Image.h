#pragma once

#include "Control.h"
#include "Render/Renderer.h"

class Image : public Control
{
private:
    /// @brief 基于的Renderer 
    Sp<Renderer> renderer;

public:
    void Draw();

    void OnAdded() override;
};