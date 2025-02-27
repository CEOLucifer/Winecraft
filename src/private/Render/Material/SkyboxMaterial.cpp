#include <glad/glad.h>
#include "Render/Material/SkyboxMaterial.h"
#include "Render/Material/Material.h"
#include "Render/Texture.h"

void SkyboxMaterial::OnInit() { DepthMask = GL_FALSE; }


void SkyboxMaterial::OnUpdateShaderProgram(Renderer& renderer, Camera& camera)
{
    updateSkybox(renderer, camera);

    // 绑定天空盒纹理
    glActiveTexture(GL_TEXTURE0);
    if (cubeTexture)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture->GetID());
    }
    else
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}