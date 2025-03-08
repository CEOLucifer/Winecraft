#include "glad/glad.h"
#include "Render/Material/InstanceMaterial.h"
#include "Core/Transform.h"
#include "Render/Shader/ShaderProgram.h"
#include <string>
#include <format>
#include "Render/Camera.h"
#include "Core/Branch.h"
#include "Render/Texture.h"
#include "Render/RenderSystem.h"


void InstanceMaterial::OnCreated(const JsonDocument& doc)
{
    Material::OnCreated(doc);

    // 材质直接保留变换数组
    transforms.reserve(100);

    for (int i = 0; i < 100; ++i)
    {
        Transform t;
        t.Position.x = (i % 10) * 3.0f;
        t.Position.y = (i / 10) * 3.0f;
        t.Position.z = 0;
        transforms.push_back(t);
    }

    // 设置uniform
    for (int i = 0; i < 100; ++i)
    {
        shaderProgram->SetMat4(std::format("models[{}]", std::to_string(i)),
                               transforms[i].GetModelMat());
    }

    EnableInstanced = true;
    InstanceCount = 100;

    diffuseTex = Resource::Load<Texture>(doc["diffuseTex"]);
    specularTex = Resource::Load<Texture>(doc["specularTex"]);
    shininess = doc["shininess"];
}

void InstanceMaterial::OnUpdateShaderProgram(Renderer& renderer, Camera& camera)
{
    shaderProgram->SetMat4("view", camera.GetParent().lock()->GetViewMat());
    shaderProgram->SetMat4("projection", camera.GetProjectionMat());


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
