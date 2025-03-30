#include "Block/BlockSystem.h"
#include "Core/Object.h"
#include "Block/BlockRenderPass.h"
#include "Block/LatticeRenderCenter.h"
#include "Core/Branch.h"

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
    lattice.Init(9, latticeRenderCenter->Get_swc());
}

void BlockSystem::Update()
{
    if (!latticeRenderCenter)
    {
        return;
    }

    lattice.Update(*latticeRenderCenter);
}

