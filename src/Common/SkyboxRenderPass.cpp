#include <glad/glad.h>
#include "Common/SkyboxRenderPass.h"
#include "Render/ShaderProgram.h"
#include "Common/CubeMesh.h"
#include "Common/Skybox.h"
#include "Render/Texture.h"
#include "Std/Math.h"
#include "Render/Camera.h"
#include "Core/Branch.h"

SkyboxRenderPass::~SkyboxRenderPass()
{
    glDeleteVertexArrays(1, &vao);
}

void SkyboxRenderPass::OnNewObject()
{
    RenderPass::OnNewObject();


    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, CubeMesh::GetInstance()->GetVbo());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, Position)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeMesh::GetInstance()->GetEbo());

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    shaderProgram = Resource::Load<ShaderProgram>("res/shaderProgram/skybox.json");

    DepthMask = GL_FALSE;
}

void SkyboxRenderPass::RenderCustom(Sp<Camera> camera)
{
    RenderPass::RenderCustom(camera);
    glBindVertexArray(vao);
    skybox->GetCubeMap()->Use(0);
    shaderProgram->Use();
    shaderProgram->SetMat4("uView", mat4(mat3(camera->GetParent().lock()->GetViewMat())));
    shaderProgram->SetMat4("uProj", camera->GetProjectionMat());
    glDrawElements(GL_TRIANGLES, CubeMesh::GetIndicesCnt(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
