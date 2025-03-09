#pragma once

#include "Typedef.h"
#include "BlendFunc.h"
#include "FaceCull.h"
#include "StencilOp.h"
#include "StencilFunc.h"
#include <GL/gl.h>
#include "Resource/Resource.h"
#include "Core/Object.h"

class Camera;
class ShaderProgram;

/// 渲染通道。用于处理某种完整的渲染过程。
class RenderPass : public Object
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
    int DepthFunc = GL_LESS;

    // 混合相关
    bool EnableBlend = false;
    BlendFunc BlendFunc;

    // 面剔除
    FaceCull FaceCull;

    uint32_t polygonMode = GL_FILL;

    /// @brief 是否启用实例化？
    bool EnableInstanced = false;

    /// @brief 在启用实例化时，实例化的个数。
    uint32_t InstanceCount = 1;

public:
    void Render(Sp<Camera> camera);

    void OnObjectCreated() override;

protected:
    virtual void RenderCustom(Sp<Camera> camera)
    {}
};