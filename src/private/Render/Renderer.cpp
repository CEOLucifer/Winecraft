#include "Render/Renderer.h"
#include "DrawMode.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render/RenderSystem.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
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
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // 投影矩阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(camera.GetFov()), camera.GetAspect(),
                         camera.GetNear(), camera.GetFar());

    // 更新shader uniform
    glUseProgram(material->shaderProgram->GetID());
    auto shaderProgram = material->shaderProgram;
    shaderProgram->OnUpdateUniform(CastTo<Renderer>(), camera);
    shaderProgram->SetMat4("model", model);
    shaderProgram->SetMat4("view", view);
    shaderProgram->SetMat4("projection", projection);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

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