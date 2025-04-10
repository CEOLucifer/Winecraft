#pragma once


#include "Std/SmartPtr.h"
#include "Render/SingletonRenderPass.h"

class Skybox;


/// 天空盒渲染通道
class SkyboxRenderPass : public SingletonRenderPass<SkyboxRenderPass>
{
private:
    Sp<Skybox> skybox;

    Sp<ShaderProgram> shaderProgram;

    u32 vao;

public:
    ~SkyboxRenderPass() override;

    void OnNewObject() override;

    void RenderCustom(Sp<Camera> camera) override;

    void SetSkybox(Sp<Skybox> value)
    {
        skybox = value;
    }
};