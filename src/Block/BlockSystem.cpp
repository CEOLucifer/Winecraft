#include "Block/BlockSystem.h"
#include "Core/Object.h"
#include "Block/BlockRenderPass.h"
#include <glm/glm.hpp>
#include "Block/LatticeRenderCenter.h"
#include "Core/Branch.h"
#include "TimeSystem.h"

using namespace std;

void BlockSystem::OnLoad()
{
    // 每帧渲染
    Object::NewObject<BlockRenderPass>();
}

void BlockSystem::SetLatticeRenderCenter(Sp<LatticeRenderCenter> value)
{
    latticeRenderCenter = value;

    // 生成地图
    lattice.Init(latticeRenderCenter->Get_swc());
}

Opt<Block> BlockSystem::GetBlock(glm::i32vec3 bwc)
{
    glm::i32vec2 lbwc = lattice.Get_swc();
    lbwc *= Section::Size;

    // 边界检查
    if (bwc.x < lbwc.x || bwc.x >= lbwc.x + Lattice::Size * Section::Size ||
        bwc.z < lbwc.y || bwc.z >= lbwc.y + Lattice::Size * Section::Size ||
        bwc.y < 0 || bwc.y >= Section::Height)
    {
        return nullopt;
    }

    glm::i32vec3 sectionCoords = {(bwc.x - lbwc.x) / Section::Size, 0, (bwc.z - lbwc.y) / Section::Size};
    glm::i32vec3 blockCoords = {(bwc.x - lbwc.x) % Section::Size, bwc.y, (bwc.z - lbwc.y) % Section::Size};
    return lattice.GetSections()[sectionCoords.x][sectionCoords.z]->Blocks[blockCoords.x][blockCoords.y][blockCoords.z];
}

float m = 0;

void BlockSystem::Update()
{
    if (!latticeRenderCenter)
    {
        return;
    }

    glm::i32vec2 swc = latticeRenderCenter->Get_swc();

    // 中心区块坐标变化，刷新网格。
    if (swc != lattice.GetCenterSectionCor())
    {
        lattice.RefreshCenter(swc);
    }

//    m += Time::GetDeltaTime();
//    if (m >= 5.0f)
//    {
//        lattice.Refresh(lattice.Get_swc() + glm::i32vec2{1, 0});
//        m = 0;
//    }
}

