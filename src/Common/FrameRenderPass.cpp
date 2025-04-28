#include <glad/glad.h>
#include "Common/FrameRenderPass.hpp"
#include "Common/CubeMesh2.hpp"
#include "Core/Branch.h"
#include "Core/Transform.h"
#include "Render/Camera.h"
#include "Render/ShaderProgram.h"

FrameRenderPass::~FrameRenderPass() { glDeleteVertexArrays(1, &vao); }

void FrameRenderPass::OnNewObject()
{
    RenderPass::OnNewObject();


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, CubeMesh2::GetInstance()->GetVbo());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeMesh2::GetInstance()->GetEbo());

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shaderProgram =
        Resource::Load<ShaderProgram>("res/shaderProgram/frame.json");

    SetRenderOrder(100);
}

void FrameRenderPass::RenderCustom(Sp<Camera> camera)
{
    // 使用着色器程序
    shaderProgram->Use();

    Transform t = {};
    t.Position = cor;
    t.Scale = {1.001, 1.001, 1.001};
    shaderProgram->SetMat4("uModel", t.GetModelMat());
    shaderProgram->SetMat4("uView", camera->GetParent().lock()->GetViewMat());
    shaderProgram->SetMat4("uProj", camera->GetProjectionMat());

    // 绑定VAO
    glBindVertexArray(vao);

    // 绘制立方体线框
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
}