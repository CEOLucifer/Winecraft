#pragma once


#include "Render/RenderPass.h"
#include "MeshControl.h"

class Canvas;
class Image;
class ShaderProgram;

/// 处理UI渲染逻辑
class UIRenderPass : public RenderPass
{
    friend class Canvas;
    friend class Image;

private:
    Sp<Canvas> canvas;
    MeshControl mesh;

    std::vector<Sp<Image>> imageVec;

    Sp<ShaderProgram> shaderProgram;

public:
    void RenderCustom(Sp<Camera> camera) override;

    void OnNewObject() override;

private:
    static Sp<UIRenderPass> instance;

public:
    static Sp<UIRenderPass> Instance()
    {
        return instance;
    }
};