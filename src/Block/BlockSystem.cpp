#include "Block/BlockSystem.h"
#include "Block/BlockRenderPass.h"
#include "Block/LatticeRenderCenter.h"
#include "Core/Branch.h"
#include "Block/StructureGenerator.h"

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


    // 测试
    SetBlock(2, {0, 0, 0});
    StructureGenerator::CreateTree({53, 80, 53});
    StructureGenerator::CreateTree({54, 80, 53});
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
//            Debug::Log(std::format("section cache:({}, {})", swc.x, swc.y));
            return section;
        }
    }
    return nullptr;
}

void BlockSystem::RemoveSectionCache(i32vec2 swc)
{
    sectionCaches.erase(swc);
}

Opt<Block> BlockSystem::GetBlock(glm::i32vec3 bwc)
{
    glm::i32vec2 lbwc = lattice.Get_swc();
    lbwc *= Section::Size;

    // 边界检查
    if (bwc.x < lbwc.x || bwc.x >= lbwc.x + lattice.GetFullSize() * Section::Size ||
        bwc.z < lbwc.y || bwc.z >= lbwc.y + lattice.GetFullSize() * Section::Size ||
        bwc.y < 0 || bwc.y >= Section::Height)
    {
        return nullopt;
    }

    glm::i32vec3 slc = {(bwc.x - lbwc.x) / Section::Size, 0, (bwc.z - lbwc.y) / Section::Size};
    glm::i32vec3 bsc = {(bwc.x - lbwc.x) % Section::Size, bwc.y, (bwc.z - lbwc.y) % Section::Size};
    auto section = lattice.GetSections()[slc.x][slc.z];
    auto block = section->Blocks[bsc.x][bsc.y][bsc.z];
    return block;
}

void BlockSystem::SetBlock(Block block, i32vec3 bwc)
{
    // 获取区块
    i32vec2 swc;

    swc.x = bwc.x >= 0 ?
            bwc.x / Section::Size :
            (bwc.x - Section::Size + 1) / Section::Size;

    swc.y = bwc.z >= 0 ?
            bwc.z / Section::Size :
            (bwc.z - Section::Size + 1) / Section::Size;

    // 从缓存中获取区块
    Sp<Section> section = GetSectionCache(swc);
    if (!section)
    {
        // 没有的话，创建新的区块
        section = Section::NewSection();
        section->Set_swc(swc);
    }


    i32vec2 bsc;
    i32 size = Section::Size;

    if (bwc.x >= 0)
    {
        bsc.x = bwc.x % Section::Size;
    }
    else
    {
        if (bwc.x % size == 0)
        {
            bsc.x = 0;
        }
        else
        {
            bsc.x = size + bwc.x % size;
        }
    }

    if (bwc.z >= 0)
    {
        bsc.y = bwc.z % Section::Size;
    }
    else
    {
        if (bwc.z % size == 0)
        {
            bsc.y = 0;
        }
        else
        {
            bsc.y = size + bwc.z % size;
        }
    }

    section->Blocks[bsc.x][bwc.y][bsc.y] = block;
}
