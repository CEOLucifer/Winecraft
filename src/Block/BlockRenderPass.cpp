#include "glad/glad.h"
#include "Block/BlockRenderPass.h"
#include "Core/Transform.h"
#include "Render/ShaderProgram.h"
#include "Render/Camera.h"
#include "Core/Branch.h"
#include "Render/Texture.h"
#include "Render/Vertex.h"
#include "Block/BlockSystem.h"

using namespace std;

Vec<Vertex> vertices = {
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
        {{-0.5f, -0.5f, 0.5f},  {-1.0f, 0.0f,  0.0f},  {1.0f, 0.0f}}
};

Vec<u32> indices = {
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

void BlockRenderPass::OnObjectCreated()
{
    RenderPass::OnObjectCreated();

    instance = CastTo<BlockRenderPass>();

//    FaceCull.Enable = true;
//    FaceCull.CullFace = GL_BACK;
//    FaceCull.FrontFace = GL_CW;

//    polygonMode = GL_LINE;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 将顶点数据从内存送到显存
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, Position)));
    glEnableVertexAttribArray(0);
    // 法线属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, Normal)));
    glEnableVertexAttribArray(1);
    // 纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, TexCoord)));
    glEnableVertexAttribArray(2);

    // todo : !!!纹理属性其实没必要，以后删



    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // 将索引数据从内存送到显存
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32),
                 indices.data(), GL_STATIC_DRAW);

    shaderProgram =
            Resource::Load<ShaderProgram>("res/shaderProgram/block.json");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BlockRenderPass::RenderCustom(Sp<Camera> camera)
{
    glBindVertexArray(vao);

    shaderProgram->Use();
    shaderProgram->SetMat4("uView", camera->GetParent().lock()->GetViewMat());
    shaderProgram->SetMat4("uProjection", camera->GetProjectionMat());

    auto texCube = Resource::Load<Texture>("res/texture/grass_block.json");
    texCube->Use(GL_TEXTURE0, GL_TEXTURE_CUBE_MAP);

    Lattice& lattice = BlockSystem::Instance()->getFrontLattice();
    // 渲染每个区块
    for (u32 xx = 0; xx < Lattice::Size; ++xx)
    {
        for (u32 zz = 0; zz < Lattice::Size; ++zz)
        {
            Sp<Section> section = lattice.Sections[xx][zz];
            // 绑定区块的VBO，然后绘制
            glBindBuffer(GL_ARRAY_BUFFER, section->GetaModelsVbo());
            // aModel 属性，实例化数组
            GLsizei vec4Size = sizeof(glm::vec4);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) 0);
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) (1 * vec4Size));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) (2 * vec4Size));
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) (3 * vec4Size));
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glVertexAttribDivisor(6, 1);

            glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, section->GetaModels().size());
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


Sp<BlockRenderPass> BlockRenderPass::instance = nullptr;
