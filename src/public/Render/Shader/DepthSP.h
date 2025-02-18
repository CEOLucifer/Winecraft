#pragma once

#include "ShaderProgram.h"

class DepthSP : public ShaderProgram
{
public:
    void OnRender(std::shared_ptr<Renderer> renderer,
                         Camera& camera) override;
};