#pragma once

#include "Core/Branch.h"
#include "Render/Renderer.h"

class Cube : public Branch
{
private:
    Sp<Renderer> renderer;

public:
    void Awake() override;
};