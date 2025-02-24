#pragma once

#include "Render/Renderer.h"

class Border : public Renderer
{
public:
    void Awake() override;

    void Update() override;
};