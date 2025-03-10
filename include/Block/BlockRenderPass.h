#pragma once

#include "Render/RenderPass.h"
#include "Singleton.h"
#include "Block/Section.h"

/// 方块渲染通道
class BlockRenderPass : public RenderPass
{
private:
    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;
    uint32_t instance_vbo = 0;

public:
    void OnObjectCreated() override;

protected:
    void RenderCustom(Sp<Camera> camera) override;

private:


    void initInstance_vbo();


private:
    static Sp<BlockRenderPass> instance;

public:
    static Sp<BlockRenderPass> Instance()
    {
        return instance;
    }
};

