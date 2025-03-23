#pragma once


#include "Render/RenderPass.h"
#include "MeshControl.h"
#include "Std/Vec.h"

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

    Vec<Sp<Image>> imageVec;

    Sp<ShaderProgram> shaderProgram;

    // 文本相关
    u32 vao;
    u32 vbo;
    Sp<ShaderProgram> textShaderProgram;

public:
    void RenderCustom(Sp<Camera> camera) override;

    void OnNewObject() override;

    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
    void initText();

private:
    static Sp<UIRenderPass> instance;

public:
    static Sp<UIRenderPass> Instance()
    {
        return instance;
    }
};