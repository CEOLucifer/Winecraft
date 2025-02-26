#include "Render/Renderer.h"
#include "Render/Material/Material.h"
#include "Camera.h"
#include "Render/Shader/ShaderProgram.h"
#include "Core/Branch.h"

void Material::updateAllTransform(Renderer& renderer, Camera& camera)
{
    shaderProgram->SetMat4("model", renderer.GetParent().lock()->GetModelMat());
    shaderProgram->SetMat4("view", camera.GetParent().lock()->GetViewMat());
    shaderProgram->SetMat4("projection", camera.GetProjectionMat());
}

void Material::updateSkybox(Renderer& renderer, Camera& camera)
{
    // 移除观察矩阵的位移分量。
    auto t = camera.GetParent();


    shaderProgram->SetMat4(
        "view", glm::mat4(glm::mat3(camera.GetParent().lock()->GetViewMat())));
    shaderProgram->SetMat4("projection", camera.GetProjectionMat());
}
