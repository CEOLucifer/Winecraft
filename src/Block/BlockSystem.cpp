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
    generateRandom_Value2();
    Object::NewObject<BlockRenderPass>();

}

void BlockSystem::generateRandom_Berlin()
{
    // 梯度向量和距离向量点乘，即高度
    // (xx, zz) 是区块坐标
    for (int xx = 0; xx < Size; ++xx)
    {
        for (int zz = 0; zz < Size; ++zz)
        {
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
                    uint32_t height = 0;

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
                    for (uint32_t y = 0; y < height; ++y)
                    {
                        sections[xx][zz].Blocks[x][y][z] = 1;
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
            // 振幅
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


void BlockSystem::generateRandom_Value2()
{
    for (int xx = 0; xx < Size; ++xx)
    {
        for (int zz = 0; zz < Size; ++zz)
        {
            for (int x = 0; x < Section::Size; ++x)
            {
                for (int z = 0; z < Section::Size; ++z)
                {
                    float height = 0;

                    height += Mathf::Noise(6, 8, 0, {xx * Section::Size + x, zz * Section::Size + z});
                    height += Mathf::Noise(32, 4, 0, {xx * Section::Size + x, zz * Section::Size + z});
                    height += Mathf::Noise(3, 1, -2, {xx * Section::Size + x, zz * Section::Size + z});
                    height += Mathf::Noise(2, 1, -2, {xx * Section::Size + x, zz * Section::Size + z});


                    for (uint32_t y = 0; y < height && y < Section::Height; ++y)
                    {
                        sections[xx][zz].Blocks[x][y][z] = 1;
                    }
                }
            }
        }
    }
}

