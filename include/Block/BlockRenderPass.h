#pragma once

#include "Render/RenderPass.h"
#include "Singleton.h"
#include "Block/Section.h"
#include <glm/glm.hpp>
#include <vector>
#include "Std/Vec.h"

/// 方块渲染通道
class BlockRenderPass : public RenderPass
{
private:
    Sp<ShaderProgram> shaderProgram;

public:
    void OnNewObject() override;

protected:
    void RenderCustom(Sp<Camera> camera) override;

private:

private:
    static Sp<BlockRenderPass> instance;

public:
    static Sp<BlockRenderPass> Instance()
    {
        return instance;
    }
};

