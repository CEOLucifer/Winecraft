#include "glad/glad.h"
#include "Block/BlockRenderPass.h"
#include <vector>
#include "Core/Transform.h"
#include "Render/ShaderProgram.h"
#include "Render/Camera.h"
#include "Core/Branch.h"
#include "Render/Texture.h"
#include "Render/Vertex.h"
#include "Block/BlockSystem.h"
#include "Block/Block.h"

using namespace std;

vector<uint32_t> indices = {
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


    vector<Vertex> vertices = {
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

    // !!!纹理属性其实没必要，以后删



    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // 将索引数据从内存送到显存
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 indices.data(), GL_STATIC_DRAW);

    shaderProgram =
            Resource::Load<ShaderProgram>("res/shaderProgram/block.json");

    initInstance_vbo();
}

void BlockRenderPass::RenderCustom(Sp<Camera> camera)
{
    glBindVertexArray(vao);

    glUseProgram(shaderProgram->GetID());
    shaderProgram->SetMat4("uView", camera->GetParent().lock()->GetViewMat());
    shaderProgram->SetMat4("uProjection", camera->GetProjectionMat());

    auto texCube = Resource::Load<Texture>("res/texture/grass_block.json");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texCube->GetID());

//    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, aModels.size());
}


Sp<BlockRenderPass> BlockRenderPass::instance = nullptr;


void BlockRenderPass::initInstance_vbo()
{
    glBindVertexArray(vao);

    aModels.reserve(Section::Size * Section::Size * Section::Height * BlockSystem::Size * BlockSystem::Size);

    // 根据区块的方块id发送aModel数据
    auto& sections = BlockSystem::Instance()->sections;

    for (int xx = 0; xx < BlockSystem::Size; ++xx)
    {
        for (int zz = 0; zz < BlockSystem::Size; ++zz)
        {
            auto& blocks = sections[xx][zz].Blocks;

            for (int x = 0; x < Section::Size; ++x)
            {
                for (int y = 0; y < Section::Height; ++y)
                {
                    for (int z = 0; z < Section::Size; ++z)
                    {
                        // 没有方块，continue
                        if (blocks[x][y][z].id == 0)
                        {
                            continue;
                        }

                        // 上下左右前后都有方块，continue
                        auto system = BlockSystem::Instance();
                        int xc = xx * Section::Size;
                        int zc = zz * Section::Size;
                        auto up = system->GetBlock({xc + x, y + 1, zc + z});
                        auto down = system->GetBlock({xc + x, y - 1, zc + z});
                        auto left = system->GetBlock({xc + x - 1, y, zc + z});
                        auto right = system->GetBlock({xc + x + 1, y, zc + z});
                        auto forward = system->GetBlock({xc + x, y, zc + z + 1});
                        auto back = system->GetBlock({xc + x, y, zc + z - 1});

                        if (up && (*up).id != 0 &&
                            down && (*down).id != 0 &&
                            left && (*left).id != 0 &&
                            right && (*right).id != 0 &&
                            forward && (*forward).id != 0 &&
                            back && (*back).id != 0)
                        {
                            continue;
                        }

                        // 添加一个此方块的aModel
                        Transform t;
                        t.Position =
                                glm::vec3(system->GetSystemCoords()) // 系统坐标
                                + glm::vec3(xx * Section::Size, 0, zz * Section::Size) // 区块坐标
                                + glm::vec3(x * 1, y * 1, z * 1); // 方块坐标
                        aModels.push_back(t.GetModelMat());
                    }
                }
            }
        }
    }
    glGenBuffers(1, &instance_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, aModels.size() * sizeof(glm::mat4), aModels.data(), GL_STATIC_DRAW);
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
}