#include <glad/glad.h>
#include "Block/Section.h"
#include "Mathf.h"
#include "Core/Transform.h"
#include "Block/BlockSystem.h"

Section::Section()
{
    u32 size = Section::Size * Section::Size * Section::Height;

    glGenBuffers(1, &aModelsVbo);
    aModels.reserve(size);

    glGenBuffers(1, &aTexIndsVbo);
    aTexInds.reserve(size);
}

Section::~Section()
{
    glDeleteBuffers(1, &aModelsVbo);
    glDeleteBuffers(1, &aTexIndsVbo);
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
}

void Section::generateRandom_Value(glm::i32vec2 swc)
{
    u32 xx = swc.x;
    u32 zz = swc.y;
    for (int x = 0; x < Section::Size; ++x)
    {
        for (int z = 0; z < Section::Size; ++z)
        {
            float height = 0;

            // 分形噪声：叠加不同振幅和周期的噪声。
            height += Mathf::Noise(32, 64, 0, {xx * Section::Size + x, zz * Section::Size + z});
            height += Mathf::Noise(32, 32, 0, {xx * Section::Size + x, zz * Section::Size + z});
//            height += Mathf::Noise(2, 4, -1, {xx * Section::Size + x, zz * Section::Size + z});
            height += Mathf::Noise(2, 8, -1, {xx * Section::Size + x, zz * Section::Size + z});

            for (u32 y = 0; y < height && y < Section::Height; ++y)
            {
                Blocks[x][y][z] = 1;
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

void Section::TransferBufferData()
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
                bool isRender = true;

                // 没有方块，continue
                if (Blocks[x][y][z] == 0)
                {
                    isRender = false;
                }
//                else
//                {
//                    // 上下左右前后都有方块，continue
//                    auto system = BlockSystem::Instance();
//                    int xc = swc.x * Section::Size;
//                    int zc = swc.y * Section::Size;
//                    auto up = system->GetBlock({xc + x, y + 1, zc + z});
//                    auto down = system->GetBlock({xc + x, y - 1, zc + z});
//                    auto left = system->GetBlock({xc + x - 1, y, zc + z});
//                    auto right = system->GetBlock({xc + x + 1, y, zc + z});
//                    auto forward = system->GetBlock({xc + x, y, zc + z + 1});
//                    auto back = system->GetBlock({xc + x, y, zc + z - 1});
//
//                    if (up && (*up).id != 0 &&
//                        down && (*down).id != 0 &&
//                        left && (*left).id != 0 &&
//                        right && (*right).id != 0 &&
//                        forward && (*forward).id != 0 &&
//                        back && (*back).id != 0)
//                    {
//                        isRender = false;
//                    }
//                }

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

                    u32 id = Blocks[x][y][z];
                    aTexInds.push_back(Blocks[x][y][z]);
                }
            }
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, aModelsVbo);
    glBufferData(GL_ARRAY_BUFFER, aModels.size() * sizeof(glm::mat4), aModels.data(), GL_DYNAMIC_DRAW);

    // aTexIndsVbo
    glBindBuffer(GL_ARRAY_BUFFER, aTexIndsVbo);
    glBufferData(GL_ARRAY_BUFFER, aTexInds.size() * sizeof(u32), aTexInds.data(), GL_DYNAMIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Section::Refresh(glm::i32vec2 swc)
{
    GenerateBlocks(swc);
    TransferBufferData();
}


Sp<Section> Section::Create()
{
    Sp<Section> This(new Section);
    return This;
}
