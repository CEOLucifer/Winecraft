#pragma once


#include "Render/RenderPass.h"
#include "Std/Vec.h"

class Canvas;
class ControlMesh;
class Image;
class ShaderProgram;
class Label;
class FontMesh;


/// 处理UI渲染逻辑
class UIRenderPass : public RenderPass
{
    friend class Canvas;
    friend class Image;
    friend class Label;

private:
    Sp<Canvas> canvas;

    // Image相关
    Sp<ControlMesh> controlMesh;
    Vec<Sp<Image>> imageVec;
    Sp<ShaderProgram> shaderProgram;

    // 文本相关
    Sp<FontMesh> fontMesh;
    Sp<ShaderProgram> textShaderProgram;
    Vec<Sp<Label>> labelVec;

public:
    void RenderCustom(Sp<Camera> camera) override;

    void OnNewObject() override;

private:
    void initText();

    void renderImages();

    void renderLabels();

private:
    static Sp<UIRenderPass> instance;

public:
    static Sp<UIRenderPass> Instance()
    {
        return instance;
    }
};