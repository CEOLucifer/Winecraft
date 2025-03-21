#include "Block/BlockSystem.h"
#include "Core/Object.h"
#include "Block/BlockRenderPass.h"
#include <glm/glm.hpp>
#include "Block/LatticeRenderCenter.h"
#include "Core/Branch.h"

using namespace std;

void BlockSystem::OnLoad()
{
    // 生成地图
    getFrontLattice().GenerateRandom({0,0});
    getFrontLattice().TransferBufferData();

    // 每帧渲染
    Object::NewObject<BlockRenderPass>();
}

Opt<Block> BlockSystem::GetBlock(glm::i32vec3 worldCor)
{
    glm::i32vec2 lc = getFrontLattice().GetCor();

    // 边界检查
    if (worldCor.x < lc.x || worldCor.x >= lc.x + Lattice::Size * Section::Size ||
        worldCor.z < lc.y || worldCor.z >= lc.y + Lattice::Size * Section::Size ||
        worldCor.y < 0 || worldCor.y >= Section::Height)
    {
        return nullopt;
    }

    glm::i32vec3 sectionCoords = {(worldCor.x - lc.x) / Section::Size, 0, (worldCor.z - lc.y) / Section::Size};
    glm::i32vec3 blockCoords = {(worldCor.x - lc.x) % Section::Size, worldCor.y, (worldCor.z - lc.y) % Section::Size};
    return getFrontLattice().Sections[sectionCoords.x][sectionCoords.z]->Blocks[blockCoords.x][blockCoords.y][blockCoords.z];
}

void BlockSystem::updateLattice()
{
    // 当前latticeRenderCenter所在区块坐标
    auto pos = latticeCenter->GetParent().lock()->Position;
    glm::i32vec2 lrcsc = {pos.x / Section::Size, pos.z / Section::Size};

    auto frontLattice = getFrontLattice();

    // 前端网格 中心区块坐标
    glm::i32vec2 csc = frontLattice.GetCenterSectionCor();

    // 判断是否相等
    // 不相等，切换网格
    if (lrcsc != csc)
    {
        // 更新后端网格
        Lattice& backLattice = getBackLattice();
        backLattice.SetCenterSectionCor(lrcsc);
        glm::i32vec2 blc = backLattice.GetCor();
        glm::i32vec2 flc = frontLattice.GetCor();

        for (int xx = 0; xx < Lattice::Size; ++xx)
        {
            for (int zz = 0; zz < Lattice::Size; ++zz)
            {
                // 是否存在于前端网格
                glm::i32vec2 cor = {blc.x + xx, blc.y + zz};
                if (flc.x <= cor.x && cor.x < flc.x + Lattice::Size
                    && flc.y <= cor.y && cor.y < flc.y + Lattice::Size)
                {
                    // 存在，赋值过来
                    glm::i32vec2 existInd = {cor.x - flc.x, cor.y - flc.y};
                    backLattice.Sections[xx][zz] = frontLattice.Sections[existInd.x][existInd.y];
                }
                else
                {
                    // 不存在，清空并重新生成
                    backLattice.Sections[xx][zz]->Clear();
                    backLattice.Sections[xx][zz]->GenerateRandom(cor);
                }
            }
        }

        // 交换前后端网格
        frontLatticeInd = (frontLatticeInd + 1) % 2;
    }
}


