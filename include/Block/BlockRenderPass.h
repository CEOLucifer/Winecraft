#pragma once

#include "Render/RenderPass.h"
#include "Singleton.h"
#include "Block/Section.h"
#include <glm/glm.hpp>
#include <vector>
#include "Aggre/Vec.h"

/// 方块渲染通道
class BlockRenderPass : public RenderPass
{
private:
    u32 vao = 0;
    u32 vbo = 0;
    u32 ebo = 0;
    u32 instance_vbo = 0;

    Vec<glm::mat4> aModels;

    Sp<ShaderProgram> shaderProgram;

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

