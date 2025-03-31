#include <glad/glad.h>
#include "Block/Section.h"
#include "Mathf.h"
#include "Core/Transform.h"
#include "Block/BlockSystem.h"
#include "Render/Vertex.h"

Section::Section()
{
}

Section::~Section()
{
    ClearOpenGL();
}

void Section::InitOpenGL()
{
    u32 size = Section::Size * Section::Size * Section::Height;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);

    glBindBuffer(GL_ARRAY_BUFFER, blockVerticeVbo);
    // 注：以下必须在vertices绑定正常数据之后才能调用。实际上是在设置当前的vao。
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, Position)));
    // 法线属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, Normal)));
    // 纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*) (offsetof(Vertex, TexCoord)));
    // todo : !!!纹理属性其实没必要，以后删

    // ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, blockVerticeEbo);
    // 只要以上这一行，就能将ebo绑定到vao了。

    // 创建其它vbo
    glGenBuffers(1, &aModelsVbo);
    aModels.reserve(size);

    glGenBuffers(1, &aTexIndsVbo);
    aTexInds.reserve(size);
}

void Section::ClearOpenGL()
{
    glDeleteBuffers(1, &aModelsVbo);
    glDeleteBuffers(1, &aTexIndsVbo);
    glDeleteVertexArrays(1, &vao);
}

void Section::FillWith(Block block)
{
    for (int x = 0; x < Size; ++x)
    {
        for (int y = 0; y < Height; ++y)
        {
            for (int z = 0; z < Size; ++z)
            {
                Blocks[x][y][z] = block;
            }
        }
    }
}


void Section::GenerateBlocks(glm::i32vec2 swc)
{
    this->swc = swc;
    Clear();
    generateRandom_Value(swc);

    BlockSystem::Instance()->CacheSection(CastTo<Section>());
}

void Section::generateRandom_Value(glm::i32vec2 swc)
{
    // 这个函数处理区块的随机生成

    u32 xx = swc.x;
    u32 zz = swc.y;
    for (int x = 0; x < Section::Size; ++x)
    {
        for (int z = 0; z < Section::Size; ++z)
        {
            glm::i32vec2 bwc = {xx * Section::Size + x, zz * Section::Size + z};


            // 高度
            u32 height = 0;
            float fHeight = 0;

            // 分形噪声：叠加不同振幅和周期的噪声。
            fHeight += Mathf::Noise(32, 64, 10, bwc);
            fHeight += Mathf::Noise(18, 32, 0, bwc);
            fHeight += Mathf::Noise(2, 8, -1, bwc);

            height = fHeight;

            for (u32 y = 0; y < height && y < Section::Height; ++y)
            {
                if (y == height - 1)
                {
                    // 表层

                    // 生态系统。目前只影响表层
                    float temperature = Mathf::Noise(1, 256, 0, bwc);
                    if (temperature < 0.3)
                    {
                        Blocks[x][y][z] = 2;
                    }
                    else if (0.3 <= temperature && temperature < 0.7)
                    {
                        Blocks[x][y][z] = 1;
                    }
                    else
                    {
                        Blocks[x][y][z] = 5;
                    }
                }
                else if (height - y > 5)
                {
                    // 泥层
                    Blocks[x][y][z] = 3;
                }
                else
                {
                    // 岩层
                    Blocks[x][y][z] = 4;
                }
            }
        }
    }
}

void Section::generateRandom_Berlin(glm::i32vec2 swc)
{
    // 梯度向量和距离向量点乘，即高度

    u32 xx = swc.x;
    u32 zz = swc.y;

    // 梯度向量
    glm::vec2 grad_1 = Mathf::GetGrad({xx, zz + 1});
    glm::vec2 grad_2 = Mathf::GetGrad({xx + 1, zz + 1});
    glm::vec2 grad_3 = Mathf::GetGrad({xx, zz});
    glm::vec2 grad_4 = Mathf::GetGrad({xx + 1, zz});

    // (x, z)是相对区块坐标
    for (int x = 0; x < Section::Size; ++x)
    {
        for (int z = 0; z < Section::Size; ++z)
        {
            u32 height = 0;

            float xa = (float) x / Section::Size;
            float za = (float) z / Section::Size;

            // 距离向量
            glm::vec2 dist_1 = {xa, za - 1};
            glm::vec2 dist_2 = {xa - 1, za - 1};
            glm::vec2 dist_3 = {xa, za};
            glm::vec2 dist_4 = {xa - 1, za};

            float influence_1 = glm::dot(grad_1, dist_1);
            float influence_2 = glm::dot(grad_2, dist_2);
            float influence_3 = glm::dot(grad_3, dist_3);
            float influence_4 = glm::dot(grad_4, dist_4);

            float a = std::lerp(influence_1, influence_2, xa);
            float b = std::lerp(influence_3, influence_4, xa);
            float c = std::lerp(b, a, za);

            // 计算高度，并限制在合理范围内
            float height_float = abs(c) * Section::Height;
            height = static_cast<uint32_t>(height_float);


            // 以height填充section
            for (u32 y = 0; y < height; ++y)
            {
                Blocks[x][y][z] = 1;
            }
        }
    }
}

void Section::FreshBufferData(Lattice& lattice)
{
    aModels.clear();
    aTexInds.clear();

    // 把每个方块的model传入
    for (int x = 0; x < Section::Size; ++x)
    {
        for (int y = 0; y < Section::Height; ++y)
        {
            for (int z = 0; z < Section::Size; ++z)
            {
                glm::mat4 model;

                // 判断方块是否应该被渲染
                bool isRender = true;
                // 没有方块，continue
                if (Blocks[x][y][z] == 0)
                {
                    isRender = false;
                }
                else
                {
                    // 上下左右前后都有方块，continue
                    int bwcX = swc.x * Section::Size;
                    int bwcY = swc.y * Section::Size;
                    auto up = lattice.GetBlock({bwcX + x, y + 1, bwcY + z});
                    auto down = lattice.GetBlock({bwcX + x, y - 1, bwcY + z});
                    auto left = lattice.GetBlock({bwcX + x - 1, y, bwcY + z});
                    auto right = lattice.GetBlock({bwcX + x + 1, y, bwcY + z});
                    auto forward = lattice.GetBlock({bwcX + x, y, bwcY + z + 1});
                    auto back = lattice.GetBlock({bwcX + x, y, bwcY + z - 1});

                    if (up && (*up).id != 0 &&
                        down && (*down).id != 0 &&
                        left && (*left).id != 0 &&
                        right && (*right).id != 0 &&
                        forward && (*forward).id != 0 &&
                        back && (*back).id != 0)
                    {
                        isRender = false;
                    }
                }

                if (isRender)
                {
                    // 添加一个此方块的aModel
                    Transform t;
                    t.Position =
                            glm::vec3(swc.x * Section::GetSize(), 0, swc.y * Section::GetSize()) // 区块的区块世界的坐标
                            + glm::vec3(x * 1, y * 1, z * 1) // 方块相对区块坐标
                            + glm::vec3(0.5, 0.5, 0.5);
                    model = t.GetModelMat();
                    aModels.push_back(model);

                    // ！！！巨坑：如上:
                    //
                    //          glm::vec3(swc.x * (int)Section::GetSize(), 0, swc.y * (int)Section::GetSize())
                    //
                    // int和u32类型相乘，必须把u32强转为int，否则默认是int强转u32。如果int是负数，则会将其变成很大的u32！还是不要用u32了！

                    aTexInds.push_back(Blocks[x][y][z]);
                }
            }
        }
    }

    glBindVertexArray(vao);
    // aModel 属性，实例化数组
    glBindBuffer(GL_ARRAY_BUFFER, aModelsVbo);
    glBufferData(GL_ARRAY_BUFFER, aModels.size() * sizeof(glm::mat4), aModels.data(), GL_DYNAMIC_DRAW);
    GLsizei vec4Size = sizeof(glm::vec4);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) 0);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) (1 * vec4Size));
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) (2 * vec4Size));
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*) (3 * vec4Size));
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    // aTexIndsVbo
    glBindBuffer(GL_ARRAY_BUFFER, aTexIndsVbo);
    glBufferData(GL_ARRAY_BUFFER, aTexInds.size() * sizeof(u32), aTexInds.data(), GL_DYNAMIC_DRAW);
    // aTexInds 属性，实例化数组
    glVertexAttribIPointer(7, 1, GL_UNSIGNED_INT, sizeof(u32), (void*) (0));
    glVertexAttribDivisor(7, 1);
    // !!!设置glsl整数类型要用glVertexAttribIPointer，而不是glVertexAttribPointer。

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

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

u32 Section::blockVerticeVbo = 0;
u32 Section::blockVerticeEbo = 0;
Vec<u32> Section::indices = {
        // 前面
        0, 1, 2, 2, 3, 0,

        // 后面
        4, 6, 5, 6, 4, 7,

        // 顶面
        8, 10, 9, 10, 8, 11,

        // 底面
        12, 13, 14, 14, 15, 12,

        // 右面
        16, 17, 18, 18, 19, 16,

        // 左面
        20, 22, 21, 22, 20, 23
};

void Section::Load()
{
    glGenBuffers(1, &blockVerticeVbo);
    glBindBuffer(GL_ARRAY_BUFFER, blockVerticeVbo);
    // 将顶点数据从内存送到显存
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &blockVerticeEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, blockVerticeEbo);
    // 将索引数据从内存送到显存
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32),
                 indices.data(), GL_STATIC_DRAW);
}

void Section::Unload()
{
    glDeleteBuffers(1, &blockVerticeEbo);
    glDeleteBuffers(1, &blockVerticeVbo);
}