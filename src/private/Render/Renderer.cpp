#include <glad/glad.h>
#include "Render/Renderer.h"
#include "Render/DrawMode.h"
#include "Render/Mesh/Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render/RenderSystem.h"
#include "Render/Camera.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Material/Material.h"
#include "Render/Addition.h"

void Renderer::Awake() { RenderSystem::Instance()->Add(CastTo<Renderer>()); }

void Renderer::OnDestroyed()
{
    RenderSystem::Instance()->Remove(CastTo<Renderer>());
}

void Renderer::Draw(Camera& camera)
{
    // 描述了一次绘制的主要过程

    if (!mesh || !material || !material->shaderProgram)
        return;

    // 顶点数据
    glBindVertexArray(mesh->GetVao());

    // 材质
    glUseProgram(material->shaderProgram->GetID());
    material->OnUpdateShaderProgram(*this, camera);
    if (addition)
    {
        addition->Add();
    }

    // 模板测试
    if (material->EnableStencilTest)
    {
        glEnable(GL_STENCIL_TEST);
        glStencilOp(material->StencilOp.stencilFail,
                    material->StencilOp.depthFail,
                    material->StencilOp.depthPass);
        glStencilFunc(material->StencilFunc.func, material->StencilFunc.ref,
                      material->StencilFunc.mask);
        glStencilMask(material->StencilMask); // 将写入的模板缓冲值
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }

    // 深度测试
    if (material->EnableDepthTest)
    {
        // 启用深度检测。此时交换链有深度字段。
        glEnable(GL_DEPTH_TEST);
        // 深度检测比较函数。默认是GL_LESS
        glDepthFunc(material->DepthFunc);
        // GL_FALSE表示不更新深度值
        glDepthMask(material->DepthMask);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    // 混合
    if (material->EnableBlend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    // 面剔除
    if (material->FaceCull.Enable)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(material->FaceCull.CullFace);
        glFrontFace(material->FaceCull.FrontFace);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    // 多边形模式
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // 调用绘制命令
    if (mesh->GetDrawMode() == Normal)
    {
        glDrawArrays(GL_TRIANGLES, 0, mesh->GetVerticeCount());
    }
    else if (mesh->GetDrawMode() == Indices)
    {
        glDrawElements(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_INT,
                       0);
    }
}

void Renderer::SetOrder(int value)
{
    order = value;
    RenderSystem::Instance()->SortAll();
}

void Renderer::SetAddition(Up<Addition> value) { addition = std::move(value); }
