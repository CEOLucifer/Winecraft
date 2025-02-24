#include <glad/glad.h>
#include "Render/Material/RealMaterial.h"
#include "Render/Material/Material.h"
#include "Render/Shader/ShaderProgram.h"
#include "Texture.h"
#include "Camera.h"
#include "Render/RenderSystem.h"
#include "Core/GameObject.h"

void RealMaterial::OnInit() {}

void RealMaterial::OnUpdateShaderProgram(Renderer& renderer, Camera& camera)
{
    Material::OnUpdateShaderProgram(renderer, camera);

    // 绑定纹理
    // ！！！目前frag shader中只有两个纹理：diffuse 和 specular。
    glActiveTexture(GL_TEXTURE0);
    if (diffuseTex)
    {
        glBindTexture(GL_TEXTURE_2D, diffuseTex->GetID());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE1);
    if (specularTex)
    {
        glBindTexture(GL_TEXTURE_2D, specularTex->GetID());
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // 绑定多个纹理。
    // for (int i = 0; i < material->texs.size(); ++i)
    // {
    //     // opengl状态里至少有16个纹理。通过下面api设置纹理。
    //     // 纹理会映射到shader的uniform sampler2D变量中。
    //     glActiveTexture(GL_TEXTURE0 + i);
    //     glBindTexture(GL_TEXTURE_2D, texs[i]->GetID());
    // }


    // 摄像机
    shaderProgram->SetVec3("viewPos", camera.GetGameObject()->Position);
    // 点光源
    auto spotLight = RenderSystem::Instance()->GetSpotLight();
    // 定向光
    auto directionalLight = RenderSystem::Instance()->GetDirectionalLight();

    if (spotLight)
    {
        shaderProgram->SetVec3("spotLight.position",
                               spotLight->GetGameObject()->Position);
        shaderProgram->SetVec3("spotLight.color", spotLight->Color);
        shaderProgram->SetVec3("spotLight.ambient", spotLight->Ambient);
        shaderProgram->SetFloat("spotLight.constant", spotLight->Constant);
        shaderProgram->SetFloat("spotLight.linear", spotLight->Linear);
        shaderProgram->SetFloat("spotLight.quadratic", spotLight->Quadratic);
    }

    if (directionalLight)
    {
        shaderProgram->SetVec3("directionLight.dir",
                               directionalLight->direction);
        shaderProgram->SetVec3("directionLight.color", directionalLight->color);
        shaderProgram->SetFloat("directionLight.intensity",
                                directionalLight->intensity);
    }

    // 材质
    shaderProgram->SetFloat("material.shininess", shininess);
}
