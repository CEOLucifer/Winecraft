#pragma once

#include "Render/BlendFunc.h"
#include "Render/FaceCull.h"
#include "Render/StencilOp.h"
#include "Render/StencilFunc.h"
#include <GL/gl.h>
#include "Resource/Resource.h"
#include "Typedef.h"

class ShaderProgram;
class Camera;
class Renderer;

/// @brief 材质
///
class Material : public Resource
{
    // 由于不同物体渲染的时设置uniform的逻辑不同，故需要派生子类。
    // 子类材质可以自定义属性，一般来说和uniform对应。然后在OnUpdateShaderProgram中设置



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
    void OnCreated(const JsonDocument& doc) override;

    /// @brief 用于更新Shader的uniform。默认：更新变换。 由子类重写。
    virtual void OnUpdateShaderProgram(Renderer& renderer, Camera& camera)
    {
        updateAllTransform(renderer, camera);
    }

protected:
    // 以下是工具函数，供子类使用

    void updateAllTransform(Renderer& renderer, Camera& camera);

    void updateSkybox(Renderer& renderer, Camera& camera);

    void updateControl(Renderer& renderer, Camera& camera);
};