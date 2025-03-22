#include "glad/glad.h"
#include "Render/RenderPass.h"
#include "Render/RenderSystem.h"

void RenderPass::Render(Sp<Camera> camera)
{
    // 模板测试
    if (EnableStencilTest)
    {
        glEnable(GL_STENCIL_TEST);
        glStencilOp(StencilOp.stencilFail,
                    StencilOp.depthFail,
                    StencilOp.depthPass);
        glStencilFunc(StencilFunc.func, StencilFunc.ref,
                      StencilFunc.mask);
        glStencilMask(StencilMask); // 将写入的模板缓冲值
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }

    // 深度测试
    if (EnableDepthTest)
    {
        // 启用深度检测。此时交换链有深度字段。
        glEnable(GL_DEPTH_TEST);
        // 深度检测比较函数。默认是GL_LESS
        glDepthFunc(DepthFunc);
        // GL_FALSE表示不更新深度值
        glDepthMask(DepthMask);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    // 混合
    if (EnableBlend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(BlendFunc.SourceFactor, BlendFunc.DestinationFactor);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    // 面剔除
    if (FaceCull.Enable)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(FaceCull.CullFace);
        glFrontFace(FaceCull.FrontFace);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    // 多边形模式
    glPolygonMode(GL_FRONT_AND_BACK, PolygonMode);

    RenderCustom(camera);
}

void RenderPass::OnNewObject()
{
    Object::OnNewObject();
    RenderSystem::Instance()->Add(CastTo<RenderPass>());
}
