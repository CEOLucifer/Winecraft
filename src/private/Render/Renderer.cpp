#include "Render/Renderer.h"
#include "DrawMode.h"
#include "Mesh.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render/RenderSystem.h"
#include "Camera.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Material.h"

void Renderer::OnInit() { RenderSystem::Instance()->Add(CastTo<Renderer>()); }

void Renderer::Draw(Camera& camera)
{
    if (!mesh || !material || !material->shaderProgram)
        return;

    glBindVertexArray(mesh->GetVao());

    // 变换
    // 世界矩阵
    // 初始化模型矩阵为单位矩阵
    glm::mat4 model = glm::mat4(1.0f);
    // 应用平移
    model = glm::translate(model, position);
    // 直接在一个矩阵上应用所有旋转
    model = glm::rotate(model, glm::radians(rotation.y),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x),
                        glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z),
                        glm::vec3(0.0f, 0.0f, 1.0f));
    // 应用缩放
    model = glm::scale(model, scale);

    // 观察矩阵
    glm::mat4 view = {1};
    view = camera.GetViewMat();

    // 投影矩阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(camera.GetFov()), camera.GetAspect(),
                         camera.GetNear(), camera.GetFar());

    // 材质
    material->OnUpdateShaderProgram(camera);

    // 将变换信息传给shader
    glUseProgram(material->shaderProgram->GetID());
    auto shaderProgram = material->shaderProgram;
    shaderProgram->SetMat4("model", model);
    shaderProgram->SetMat4("view", view);
    shaderProgram->SetMat4("projection", projection);

    // 模板测试
    glStencilOp(StencilOp.stencilFail, StencilOp.depthFail,
                StencilOp.depthPass);
    glStencilFunc(StencilFunc.func, StencilFunc.ref, StencilFunc.mask);
    glStencilMask(StencilMask); // 将写入的模板缓冲值

    // 深度测试
    if (EnableDepthTest)
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

    // 混合
    if (EnableBlend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // 调用绘制命令
    if (mesh->GetDrawMode() == Normal)
    {
        glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertices().size());
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
