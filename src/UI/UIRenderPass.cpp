#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include "UI/UIRenderPass.h"
#include "Render/ShaderProgram.h"
#include "Core/Branch.h"
#include "UI/Image.h"
#include "Render/RenderSystem.h"
#include "Render/Texture.h"
#include "Font/Character.h"

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

    // 测试：文本渲染
    RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
    RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
}

void UIRenderPass::OnNewObject()
{
    RenderPass::OnNewObject();

    EnableDepthTest = false;
    EnableBlend = true;

    shaderProgram =
            Resource::Load<ShaderProgram>("res/shaderProgram/control.json");

    instance = CastTo<UIRenderPass>();

    initText();
}

void UIRenderPass::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // 激活对应的渲染状态
    textShaderProgram->Use();
    textShaderProgram->SetVec3("textColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    // 遍历文本中所有的字符
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Character::Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // 对每个字符更新VBO
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos + h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}
        };
        // 在四边形上绘制字形纹理
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // 更新VBO内存的内容
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // 绘制四边形
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // 更新位置到下一个字形的原点，注意单位是1/64像素
        x += (ch.Advance >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void UIRenderPass::initText()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    textShaderProgram = Resource::Load<ShaderProgram>("res/shaderProgram/font.json");
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    textShaderProgram->SetMat4("projection", projection);

    Character::LoadCharacters();
}

Sp<UIRenderPass> UIRenderPass::instance = nullptr;

