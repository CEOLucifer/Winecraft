#include "Render/Renderer.h"
#include "Render/Material/Material.h"
#include "Camera.h"
#include "Render/Shader/ShaderProgram.h"
#include "Core/GameObject.h"

void Material::updateAllTransform(Renderer& renderer, Camera& camera)
{
    shaderProgram->SetMat4("model", renderer.GetGameObject()->GetModelMat());
    shaderProgram->SetMat4("view", camera.GetGameObject()->GetViewMat());
    shaderProgram->SetMat4("projection", camera.GetProjectionMat());
}

void Material::updateSkybox(Renderer& renderer, Camera& camera)
{
    // 移除观察矩阵的位移分量。
    shaderProgram->SetMat4("view", glm::mat4(glm::mat3(camera.GetGameObject()->GetViewMat())));
    shaderProgram->SetMat4("projection", camera.GetProjectionMat());
}