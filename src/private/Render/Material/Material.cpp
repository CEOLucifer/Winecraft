#include "Render/Renderer.h"
#include "Render/Material/Material.h"
#include "Camera.h"
#include "Render/Shader/ShaderProgram.h"

void Material::updateAllTransform(Renderer& renderer, Camera& camera)
{
    shaderProgram->SetMat4("model", renderer.GetModelMat());
    shaderProgram->SetMat4("view", camera.GetViewMat());
    shaderProgram->SetMat4("projection", camera.GetProjectionMat());
}

void Material::updateSkybox(Renderer& renderer, Camera& camera)
{
    // 移除观察矩阵的位移分量。
    shaderProgram->SetMat4("view", glm::mat4(glm::mat3(camera.GetViewMat())));
    shaderProgram->SetMat4("projection", camera.GetProjectionMat());
}