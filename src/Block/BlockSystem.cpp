#include "Block/BlockSystem.h"
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
    lattice.Init(9);
    lattice.RefreshCenter(value->Get_swc());
}

void BlockSystem::Update()
{
    if (!latticeRenderCenter)
    {
        return;
    }

    lattice.Update(*latticeRenderCenter);
}

void BlockSystem::CacheSection(Sp<Section> section)
{
    if (IsCachedSection(section->Get_swc()))
    {
        return;
    }

    sectionCaches.insert({section->Get_swc(), section});
}

Sp<Section> BlockSystem::GetSectionCache(glm::i32vec2 swc)
{
    for (auto each: sectionCaches)
    {
        Sp<Section> section = each.second;
        if (section->Get_swc() == swc)
        {
            Debug::Log(std::format("section cache:({}, {})", swc.x, swc.y));
            return section;
        }
    }
    return nullptr;
}