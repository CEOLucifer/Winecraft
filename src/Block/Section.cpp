#include "glad/glad.h"
#include "Block/Section.h"
#include "Render/Vertex.h"
#include <vector>
#include "Render/Shader/ShaderProgram.h"
#include "Core/Transform.h"
#include "Render/Camera.h"
#include "Core/Branch.h"
#include "Render/Texture.h"


using namespace std;

void Section::Draw(Sp<Camera> camera)
{
    glBindVertexArray(vao);
    glUseProgram(shaderProgram->GetID());
    shaderProgram->SetMat4("uView", camera->GetParent().lock()->GetViewMat());
    shaderProgram->SetMat4("uProjection", camera->GetProjectionMat());

    // 绑定方块纹理
    auto tex = Resource::Load<Texture>("res/texture/skybox.json");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex->GetID());

    // 绘制
    glDrawElements(GL_FILL, indices.size(),
                   GL_UNSIGNED_INT, 0);
}


Section Section::New()
{
    Section This = {};
    glGenVertexArrays(1, &This.vao);
    glBindVertexArray(This.vao);

    glGenBuffers(1, &This.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, This.vbo);
    This.vertices = {
            // 前面
            {{-0.5f, -0.5f, 0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f}},
            {{0.5f,  -0.5f, 0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f}},
            {{-0.5f, 0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 1.0f}},
            // 后面
            {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f,  -1.0f}, {1.0f, 0.0f}},
            {{0.5f,  -0.5f, -0.5f}, {0.0f,  0.0f,  -1.0f}, {0.0f, 0.0f}},
            {{0.5f,  0.5f,  -0.5f}, {0.0f,  0.0f,  -1.0f}, {0.0f, 1.0f}},
            {{-0.5f, 0.5f,  -0.5f}, {0.0f,  0.0f,  -1.0f}, {1.0f, 1.0f}},
            // 顶面
            {{-0.5f, 0.5f,  -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
            {{0.5f,  0.5f,  -0.5f}, {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
            {{-0.5f, 0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}},
            // 底面
            {{-0.5f, -0.5f, -0.5f}, {0.0f,  -1.0f, 0.0f},  {0.0f, 1.0f}},
            {{0.5f,  -0.5f, -0.5f}, {0.0f,  -1.0f, 0.0f},  {1.0f, 1.0f}},
            {{0.5f,  -0.5f, 0.5f},  {0.0f,  -1.0f, 0.0f},  {1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f},  {0.0f,  -1.0f, 0.0f},  {0.0f, 0.0f}},
            // 右面
            {{0.5f,  -0.5f, -0.5f}, {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
            {{0.5f,  0.5f,  -0.5f}, {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
            {{0.5f,  -0.5f, 0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
            // 左面
            {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f,  0.0f},  {0.0f, 0.0f}},
            {{-0.5f, 0.5f,  -0.5f}, {-1.0f, 0.0f,  0.0f},  {0.0f, 1.0f}},
            {{-0.5f, 0.5f,  0.5f},  {-1.0f, 0.0f,  0.0f},  {1.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f},  {-1.0f, 0.0f,  0.0f},  {1.0f, 0.0f}}};
    glBufferData(GL_ARRAY_BUFFER, This.vertices.size() * sizeof(Vertex),
                 This.vertices.data(), GL_STATIC_DRAW);
    // 位置属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, Position)));
    // 法线属性
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, Normal)));
    // 纹理属性
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, TexCoord)));


    This.indices = {
            // 前面
            0, 1, 2, 2, 3, 0,
            // 后面
            4, 5, 6, 6, 7, 4,
            // 顶面
            8, 9, 10, 10, 11, 8,
            // 底面
            12, 13, 14, 14, 15, 12,
            // 右面
            16, 17, 18, 18, 19, 16,
            // 左面
            20, 21, 22, 22, 23, 20
    };
    glGenBuffers(1, &This.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, This.ebo);
    // 将索引数据从内存送到显存
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, This.indices.size() * sizeof(uint32_t),
                 This.indices.data(), GL_STATIC_DRAW);



    // instance vbo
    vector<glm::mat4> models;
    models.reserve(32 * 32 * 32);
    for (int x = 0; x < 32; ++x)
    {
        for (int y = 0; y < 32; ++y)
        {
            for (int z = 0; z < 32; ++z)
            {
                Transform transform = {};
                transform.Position = {x * 1, y * 1, z * 1};
                models.push_back(transform.GetModelMat());
            }
        }
    }


    glGenBuffers(1, &This.instance_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, This.instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * models.size(), models.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT_MAT4, GL_FALSE, sizeof(glm::mat4), (void*) 0);
    glVertexAttribDivisor(3, 1); // tell OpenGL this is an instanced vertex attribute.



    // shaderProgram
    This.shaderProgram = Resource::Load<ShaderProgram>("res/shaderProgram/block.json");
    This.shaderProgram->SetInt("tex0", 0);

    return This;
}
