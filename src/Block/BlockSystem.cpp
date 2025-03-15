#include "Block/BlockSystem.h"
#include "Core/Object.h"
#include "Block/BlockRenderPass.h"
#include <glm/glm.hpp>
#include "Mathf.h"

using namespace std;

void BlockSystem::OnLoad()
{
    initSectionsSize();
//    generateRandom_Berlin();
    generateRandom_Value();
    Object::NewObject<BlockRenderPass>();

}

void BlockSystem::generateRandom_Berlin()
{
    // 柏林噪声生成高度

    // 随机梯度向量
    glm::vec2 grads[6][6];
    for (int x = 0; x < 6; ++x)
    {
        for (int z = 0; z < 6; ++z)
        {
            grads[x][z] = Mathf::RandomDir2D();
        }
    }

    // 梯度向量和距离向量点乘，即高度
    // (i, j) 是区块坐标
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            // 梯度向量
            glm::vec2 grad_1 = grads[i][j];
            glm::vec2 grad_2 = grads[i + 1][j];
            glm::vec2 grad_3 = grads[i + 1][j + 1];
            glm::vec2 grad_4 = grads[i][j + 1];

            // 距离向量。总是选取晶格中点
            glm::vec2 dist_1 = {0.5, 0.5};
            glm::vec2 dist_2 = {-0.5, 0.5};
            glm::vec2 dist_3 = {-0.5, -0.5};
            glm::vec2 dist_4 = {0.5, -0.5};

            float influence_1 = glm::dot(dist_1, grad_1);
            float influence_2 = glm::dot(dist_2, grad_2);
            float influence_3 = glm::dot(dist_3, grad_3);
            float influence_4 = glm::dot(dist_4, grad_4);


            // (x, z)是相对区块坐标
            for (int x = 0; x < 32; ++x)
            {
                for (int z = 0; z < 32; ++z)
                {
                    float height = 0;

                    float a = std::lerp(influence_1, influence_2, (float) x / 32);
                    float b = std::lerp(influence_3, influence_4, (float) x / 32);
                    float c = std::lerp(a, b, (float) z / 32);

                    // 计算高度
                    height = (c + 0.5f) * 32;

                    height = std::clamp(height, 1.0f, 32.0f);

                    // 以height填充section
                    for (int y = 0; y < height; ++y)
                    {
                        sections[i][j].Blocks[x][y][z] = 1;
                    }
                }
            }
        }
    }


}


std::optional<Block> BlockSystem::GetBlock(glm::i32vec3 worldCoords)
{
    glm::i32vec3 sysCoords = GetSystemCoords();

    // 边界检查
    if (worldCoords.x < sysCoords.x || worldCoords.x >= sysCoords.x + Size * Section::Size ||
        worldCoords.z < sysCoords.z || worldCoords.z >= sysCoords.z + Size * Section::Size ||
        worldCoords.y < 0 || worldCoords.y >= Section::Height)
    {
        return nullopt;
    }

    glm::i32vec3 sectionCoords = {(worldCoords.x - sysCoords.x) / Section::Size, 0, (worldCoords.z - sysCoords.z) / Section::Size};
    glm::i32vec3 blockCoords = {(worldCoords.x - sysCoords.x) % Section::Size, worldCoords.y, (worldCoords.z - sysCoords.z) % Section::Size};
    return sections[sectionCoords.x][sectionCoords.z].Blocks[blockCoords.x][blockCoords.y][blockCoords.z];
}

void BlockSystem::initSectionsSize()
{
    // Size * Size
    sections.resize(Size);
    for (auto& each: sections)
    {
        each.resize(Size);
    }
}

void BlockSystem::generateRandom_Value()
{
    for (int xx = 0; xx < Size; ++xx)
    {
        for (int zz = 0; zz < Size; ++zz)
        {
            uint32_t y1 = Mathf::GetHeight({xx, zz + 1});
            uint32_t y2 = Mathf::GetHeight({xx + 1, zz + 1});
            uint32_t y3 = Mathf::GetHeight({xx, zz});
            uint32_t y4 = Mathf::GetHeight({xx + 1, zz});

            for (int x = 0; x < Section::Size; ++x)
            {
                for (int z = 0; z < Section::Size; ++z)
                {
                    float height;

                    float a = (float) x / Section::Size;
                    float b = (float) z / Section::Size;

                    height = lerp(lerp(y3, y4, Mathf::Fade(a)), lerp(y1, y2, Mathf::Fade(a)), Mathf::Fade(b));

                    for (uint32_t y = 0; y < height; ++y)
                    {
                        sections[xx][zz].Blocks[x][y][z] = 1;
                    }
                }
            }
        }
    }
}


