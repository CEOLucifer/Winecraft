#include "glad/glad.h"
#include "Render/Material/ControlMaterial.h"
#include "Render/RenderSystem.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Renderer.h"

void ControlMaterial::OnUpdateShaderProgram(Renderer& renderer, Camera& camera)
{
    updateControl(renderer, camera);

    auto& shaderProgram = renderer.GetMaterial()->shaderProgram;
    shaderProgram->SetVec2(
            "viewportSize", RenderSystem::Instance()->GetWindowSize());
}