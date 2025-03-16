#include <glad/glad.h>
#include "UI/UIRenderPass.h"
#include "Render/ShaderProgram.h"
#include "Core/Branch.h"
#include "UI/Image.h"
#include "Render/RenderSystem.h"
#include "Render/Texture.h"

void UIRenderPass::RenderCustom(Sp<Camera> camera)
{
    mesh.Use();
    shaderProgram->Use();

    glm::vec2 viewportSize = RenderSystem::Instance()->GetWindowSize();
    // 遍历每个Image
    for (auto each: imageVec)
    {
        glActiveTexture(GL_TEXTURE0);
        if (each->GetTex())
        {
            glBindTexture(GL_TEXTURE_2D, each->GetTex()->GetID());
        }

        Sp<Branch> branch = each->GetParent().lock();
        Transform t = *branch;
        t.Position.x /= viewportSize.x / 2;
        t.Position.y /= viewportSize.y / 2;
        t.Scale.x /= viewportSize.x / 2;
        t.Scale.y /= viewportSize.y / 2;

        shaderProgram->SetMat4("uModel", t.GetModelMat());
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void UIRenderPass::OnObjectCreated()
{
    RenderPass::OnObjectCreated();

    EnableDepthTest = false;
    EnableBlend = true;

    shaderProgram =
            Resource::Load<ShaderProgram>("res/shaderProgram/control.json");

    instance = CastTo<UIRenderPass>();
}

Sp<UIRenderPass> UIRenderPass::instance = nullptr;
