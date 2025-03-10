#include "Block/BlockSystem.h"
#include "Core/Object.h"
#include "Block/BlockRenderPass.h"
#include <glm/glm.hpp>
#include "Mathf.h"

void BlockSystem::OnLoad()
{
    initSections();

    Object::Create<BlockRenderPass>();
}

void BlockSystem::initSections()
{
    // 5 x 5
    sections.resize(5);
    for (auto& each: sections)
    {
        each.resize(5);
    }

    // 柏林噪声生成高度


    // 随机梯度向量
    glm::vec2 grads[6][6];
    for (int x = 0; x < 6; ++x)
    {
        for (int z = 0; z < 6; ++z)
        {
            grads[x][z] = glm::normalize(glm::vec2{std::rand(), std::rand()});
        }
    }

    // 梯度向量和距离向量点乘，即高度
    // (i, j) 是区块坐标
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            // (x, z)是相对区块坐标
            for (int x = 0; x < 32; ++x)
            {
                for (int z = 0; z < 32; ++z)
                {
                    int height = 0;

//                    // 距离向量
//                    glm::vec2 dist_1 = {x - 0, z - 0};
//                    glm::vec2 dist_2 = {x - 32, z - 0};
//                    glm::vec2 dist_3 = {x - 32, z - 32};
//                    glm::vec2 dist_4 = {x - 0, z - 32};
//
//                    // 梯度向量
//                    glm::vec2 grad_1 = grads[i][j];
//                    glm::vec2 grad_2 = grads[i + 1][j];
//                    glm::vec2 grad_3 = grads[i + 1][j + 1];
//                    glm::vec2 grad_4 = grads[i][j + 1];
//
//                    // 计算高度
//                    height = glm::dot(dist_1, grad_1) + glm::dot(dist_2, grad_2) + glm::dot(dist_3, grad_3) + glm::dot(dist_4, grad_4);
//                    height = std::clamp(height, 0, 32);

                    height = Mathf::RandomIntRange(0, 32);

                    // 以height填充section
                    for(int y = 0; y < height; ++y)
                    {
                        sections[i][j].Blocks[x][y][z] = 1;
                    }
                }
            }
        }
    }


}