#include <glad/glad.h>
#include "Render/Renderer.h"
#include "DrawMode.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render/RenderSystem.h"
#include "Camera.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Material/Material.h"

void Renderer::OnInit() { RenderSystem::Instance()->Add(CastTo<Renderer>()); }

void Renderer::Draw(Camera& camera)
{
    if (!mesh || !material || !material->shaderProgram)
        return;

    glBindVertexArray(mesh->GetVao());
    
    // 材质
    glUseProgram(material->shaderProgram->GetID());
    material->OnUpdateShaderProgram(*this, camera);

    // 模板测试
    glStencilOp(material->StencilOp.stencilFail, material->StencilOp.depthFail,
                material->StencilOp.depthPass);
    glStencilFunc(material->StencilFunc.func, material->StencilFunc.ref,
                  material->StencilFunc.mask);
    glStencilMask(material->StencilMask); // 将写入的模板缓冲值

    // 深度测试
    if (material->EnableDepthTest)
    {
        // 启用深度检测。此时交换链有深度字段。
        glEnable(GL_DEPTH_TEST);
        // 深度检测比较函数。默认是GL_LESS
        // glDepthFunc(GL_LESS);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    glDepthMask(material->DepthMask);

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
