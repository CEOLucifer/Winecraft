#include "Render/Material/SingleColorMaterial.h"
#include "Render/Shader/ShaderProgram.h"

void SingleColorMaterial::OnUpdateShaderProgram(Renderer& renderer,
                                                Camera& camera)
{
    Material::OnUpdateShaderProgram(renderer, camera);
    shaderProgram->SetVec3("color", Color);
}