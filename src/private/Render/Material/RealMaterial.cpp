#include <glad/glad.h>
#include "Render/Material/RealMaterial.h"
#include "Render/Material/Material.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Texture.h"
#include "Render/Camera.h"
#include "Render/RenderSystem.h"
#include "Core/Node.h"
#include "Core/Branch.h"
#include "Resource/Resource.h"

void RealMaterial::OnCreated(const JsonDocument& doc)
{
    Material::OnCreated(doc);
    diffuseTex = Resource::Load<Texture>(doc["diffuseTex"]);
    specularTex = Resource::Load<Texture>(doc["specularTex"]);
    shininess = doc["shininess"];
}

void RealMaterial::OnUpdateShaderProgram(Renderer& renderer, Camera& camera)
{
    // 此函数可以当作示例。
    // 若重复设置同一全局uniform，可以考虑last判断

    updateAllTransform(renderer, camera);

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
    shaderProgram->SetVec3("viewPos", camera.GetParent().lock()->Position);
    // 点光源
    auto spotLight = RenderSystem::Instance()->GetSpotLight();
    // 定向光
    auto directionalLight = RenderSystem::Instance()->GetDirectionalLight();

    if (spotLight)
    {
        shaderProgram->SetVec3("spotLight.position",
                               spotLight->GetParent().lock()->Position);
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
