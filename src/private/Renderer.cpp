#include "Render/Renderer.h"
#include "DrawMode.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render/RenderSystem.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Render/Material.h"

void Renderer::OnInit() { RenderSystem::Instance()->Add(CastTo<Renderer>()); }

void Renderer::Draw(Camera& camera)
{
    if (!mesh || !material || !material->shaderProgram)
        return;

    glBindVertexArray(mesh->GetVao());
    glUseProgram(material->shaderProgram->GetID());

    // 旧版：绑定纹理。
    // for (int i = 0; i < material->texs.size(); ++i)
    // {
    //     // opengl状态里至少有16个纹理。通过下面api设置纹理。
    //     // 纹理会映射到shader的uniform sampler2D变量中。
    //     glActiveTexture(GL_TEXTURE0 + i);
    //     glBindTexture(GL_TEXTURE_2D, texs[i]->GetID());
    // }

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


    auto shaderProgram = material->shaderProgram;
    // 摄像机
    shaderProgram->SetVec3("viewPos", camera.position);
    // 点光源
    auto spotLight = RenderSystem::Instance()->GetSpotLight();
    // 定向光
    auto directionalLight = RenderSystem::Instance()->GetDirectionalLight();
    shaderProgram->SetVec3("spotLight.position", spotLight->position);
    shaderProgram->SetVec3("spotLight.color", spotLight->Color);
    shaderProgram->SetVec3("spotLight.ambient", spotLight->Ambient);
    shaderProgram->SetVec3("directionLight.dir", directionalLight->direction);
    shaderProgram->SetVec3("directionLight.color", directionalLight->color);
    shaderProgram->SetFloat("directionLight.intensity",
                            directionalLight->intensity);

    shaderProgram->SetFloat("material.shininess", material->shininess);

    // 变换
    // 世界矩阵
    // 初始化模型矩阵为单位矩阵
    glm::mat4 model = glm::mat4(1.0f);

    // 应用平移
    model = glm::translate(model, position);

    // 直接在一个矩阵上应用所有旋转
    model = glm::rotate(model, glm::radians(rotation.y),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x),
                        glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z),
                        glm::vec3(0.0f, 0.0f, 1.0f));

    // 应用缩放
    model = glm::scale(model, scale);





    // 观察矩阵
    glm::mat4 view = {1};
    view = camera.GetViewMat();
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // 投影矩阵
    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(camera.GetFov()), camera.GetAspect(),
                         camera.GetNear(), camera.GetFar());

    shaderProgram->SetMat4("model", model);
    shaderProgram->SetMat4("view", view);
    shaderProgram->SetMat4("projection", projection);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    if (mesh->GetDrawMode() == Normal)
    {
        glDrawArrays(GL_TRIANGLES, 0, mesh->GetVertices().size());
    }
    else if (mesh->GetDrawMode() == Indices)
    {
        glDrawElements(GL_TRIANGLES, mesh->GetIndices().size(), GL_UNSIGNED_INT,
                       0);
    }
}