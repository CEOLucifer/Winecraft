#pragma once

#include "Render/RenderPass.h"
#include "Std/Math.h"

/// @brief 方块线框渲染通道
class FrameRenderPass : public RenderPass
{
private:
    Sp<ShaderProgram> shaderProgram;

    u32 vao;

    /// @brief 方块线框坐标 
    vec3 cor = {0, 0, 0};

public:
    ~FrameRenderPass();

    void OnNewObject() override;

    void RenderCustom(Sp<Camera> camera) override;

    void SetCor(vec3 value) { cor = value; }
};