#include <glad/glad.h>
#include "Render/Material/ControlMaterial.h"
#include "Render/Shader/ShaderProgram.h"

void ControlMaterial::OnUpdateShaderProgram(Renderer& renderer, Camera& camera)
{
    glActiveTexture(GL_TEXTURE0);
    if (texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture->GetID());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}