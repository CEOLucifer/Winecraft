#include "Render/SingleColorMaterial.h"
#include "Render/Shader/ShaderProgram.h"

void SingleColorMaterial::OnUpdateShaderProgram(Camera& camera)
{
    shaderProgram->SetVec3("color", Color);
}