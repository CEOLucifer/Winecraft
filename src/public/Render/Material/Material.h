#pragma once

#include "Render/BlendFunc.h"
#include "Render/FaceCull.h"
#include "Render/StencilOp.h"
#include "Render/StencilFunc.h"
#include <GL/gl.h>
#include "Typedef.h"

class ShaderProgram;
class Camera;
class Renderer;

/// @brief 材质
///
class Material
{
public:
    /// @brief shader程序
    Sp<ShaderProgram> shaderProgram;

    // 模板测试相关
    bool EnableStencilTest = true;
    StencilOp StencilOp;
    StencilFunc StencilFunc;
    int StencilMask = 0x00;

    // 深度测试相关
    bool EnableDepthTest = true;
    int DepthMask = GL_TRUE;

    // 混合相关

    bool EnableBlend = false;
    BlendFunc BlendFunc;

    // 面剔除
    FaceCull FaceCull;


public:
    /// @brief 用于配置默认属性
    virtual void OnInit() {}

    /// @brief 用于更新Shader的uniform。默认：更新变换。 由子类重写。
    virtual void OnUpdateShaderProgram(Renderer& renderer, Camera& camera) { updateAllTransform(renderer, camera); }

protected:
    void updateAllTransform(Renderer& renderer, Camera& camera);

    void updateSkybox(Renderer& renderer, Camera& camera);
};

class MaterialFactory
{
public:
    template <typename T> static Sp<T> CreateRaw()
    {
        Sp<T> This(new T);
        This->OnInit();
        return This;
    }
};