#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include "UI/UIRenderPass.h"
#include "Render/ShaderProgram.h"
#include "Core/Branch.h"
#include "UI/Image.h"
#include "Render/RenderSystem.h"
#include "Render/Texture.h"
#include "Font/Character.h"
#include "UI/Label.h"
#include "UI/FontMesh.h"
#include "UI/ControlMesh.h"
#include "Render/Vertex2.h"

void UIRenderPass::RenderCustom(Sp<Camera> camera)
{
    renderImages();
    renderLabels();
}

void UIRenderPass::OnNewObject()
{
    RenderPass::OnNewObject();

    EnableDepthTest = false;
    EnableBlend = true;


    instance = CastTo<UIRenderPass>();

    controlMesh = ControlMesh::Create();
    shaderProgram =
            Resource::Load<ShaderProgram>("res/shaderProgram/control.json");

    initText();
}

void UIRenderPass::initText()
{
    textShaderProgram = Resource::Load<ShaderProgram>("res/shaderProgram/font.json");
    fontMesh = FontMesh::Create();
}

void UIRenderPass::renderImages()
{
    controlMesh->Use();
    shaderProgram->Use();
    glm::vec2 viewportSize = RenderSystem::Instance()->GetWindowSize();
    shaderProgram->SetMat4("uProj", glm::ortho(0.0f, viewportSize.x, 0.0f, viewportSize.y));
    // 遍历每个Image
    for (auto image: imageVec)
    {
        if (image->GetTex())
        {
            image->GetTex()->Use(GL_TEXTURE0);
        }

        Sp<Branch> branch = image->GetParent().lock();
        Transform t = *branch;
        shaderProgram->SetMat4("uModel", t.GetModelMat());
        shaderProgram->SetVec4("uColor", image->GetColor());
        glDrawElements(GL_TRIANGLES, controlMesh->GetIndiceCount(), GL_UNSIGNED_INT, 0);
    }
}

void UIRenderPass::renderLabels()
{
    // 激活对应的渲染状态
    fontMesh->Use();
    textShaderProgram->Use();
    glActiveTexture(GL_TEXTURE0);
    glm::vec2 viewportSize = RenderSystem::Instance()->GetWindowSize();
    textShaderProgram->SetMat4("uProj", glm::ortho(0.0f, viewportSize.x, 0.0f, viewportSize.y));

    for (auto label: labelVec)
    {
        textShaderProgram->SetVec4("uColor", label->GetColor());
        String& text = label->GetText();
        Sp<Font> font = label->GetFont();
        f32 fontSize = label->GetFontSize();
        glm::vec2 labPos = label->GetPos();

        glm::vec2 pos = {0, 0};

        // 遍历文本中所有的字符，逐个渲染字符。
        for (auto c = text.begin(); c != text.end(); c++)
        {
            Character& ch = font->GetCharacter(*c);

            f32 xpos = pos.x + ch.Bearing.x * fontSize;
            f32 ypos = pos.y - (ch.Size.y - ch.Bearing.y) * fontSize;

            f32 w = ch.Size.x * fontSize;
            f32 h = ch.Size.y * fontSize;

            // 字符的顶点坐标
            Vertex2 vertices[6] = {
                    {labPos + glm::vec2{xpos, ypos + h},     {0.0, 0.0}},
                    {labPos + glm::vec2{xpos, ypos},         {0.0, 1.0}},
                    {labPos + glm::vec2{xpos + w, ypos},     {1.0, 1.0}},
                    {labPos + glm::vec2{xpos, ypos + h},     {0.0, 0.0}},
                    {labPos + glm::vec2{xpos + w, ypos},     {1.0, 1.0}},
                    {labPos + glm::vec2{xpos + w, ypos + h}, {1.0, 0.0}}
            };

            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, fontMesh->GetVbo());
            glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(Vertex2), vertices); // Be sure to use glBufferSubData and not glBufferData
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            pos.x += (ch.Advance >> 6) * fontSize; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Sp<UIRenderPass> UIRenderPass::instance = nullptr;

