#pragma once

#include "Render/Renderer.h"

class Border : public Renderer
{
public:
    void OnInit() override;

    void OnUpdate(float deltaTime) override;
};