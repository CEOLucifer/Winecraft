#include "Render/Shader/UniversalShaderProgram.h"
#include "Render/Renderer.h"
#include "Render/Material.h"
#include "Render/RenderSystem.h"
#include "Texture.h"
#include "Camera.h"

void UniversalShaderProgram::onSetTextureLocation()
{
    // 设置uniform纹理位置。这一步和Renderer Draw函数中glActiveTexture对应。
    SetInt("material.diffuse", 0);
    SetInt("material.specular", 1);
}

void UniversalShaderProgram::OnRender(std::shared_ptr<Renderer> renderer,
                                             Camera& camera)
{
    // 旧版：绑定纹理。
    // for (int i = 0; i < material->texs.size(); ++i)
    // {
    //     // opengl状态里至少有16个纹理。通过下面api设置纹理。
    //     // 纹理会映射到shader的uniform sampler2D变量中。
    //     glActiveTexture(GL_TEXTURE0 + i);
    //     glBindTexture(GL_TEXTURE_2D, texs[i]->GetID());
    // }

    auto material = renderer->GetMaterial();

    // 绑定纹理
    // ！！！目前frag shader中只有两个纹理：diffuse 和 specular。
    if (material->diffuseTex)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material->diffuseTex->GetID());
    }
    if (material->specularTex)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, material->specularTex->GetID());
    }


    // 摄像机
    SetVec3("viewPos", camera.position);
    // 点光源
    auto spotLight = RenderSystem::Instance()->GetSpotLight();
    // 定向光
    auto directionalLight = RenderSystem::Instance()->GetDirectionalLight();
    SetVec3("spotLight.position", spotLight->position);
    SetVec3("spotLight.color", spotLight->Color);
    SetVec3("spotLight.ambient", spotLight->Ambient);
    SetFloat("spotLight.constant", spotLight->Constant);
    SetFloat("spotLight.linear", spotLight->Linear);
    SetFloat("spotLight.quadratic", spotLight->Quadratic);
    SetVec3("directionLight.dir", directionalLight->direction);
    SetVec3("directionLight.color", directionalLight->color);
    SetFloat("directionLight.intensity", directionalLight->intensity);
    // 材质
    SetFloat("material.shininess", material->shininess);
}
