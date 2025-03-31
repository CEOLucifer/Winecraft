#include "Block/Lattice.h"
#include "Debug/Debug.h"
#include "Block/LatticeRenderCenter.h"
#include "Block/BlockSystem.h"

using namespace std;

void Lattice::Init(u32 renderSize)
{
    if ((renderSize & 1) == 0)
    {
        Debug::LogError("renderSize必须是奇数");
    }

    // 用nullptr填充Sections
    u32 fullSize = renderSize + 2;
    sections.resize(fullSize);
    for (i32 xx = 0; xx < fullSize; ++xx)
    {
        sections[xx].resize(fullSize);
        for (i32 zz = 0; zz < fullSize; ++zz)
        {
            sections[xx][zz] = Object::NewObject<Section>();
        }
    }
}

void Lattice::Refresh(glm::i32vec2 swc)
{
    if (this->swc == swc)
    {
        return;
    }

    this->swc = swc;

    glm::i32vec2 old_swc = this->swc;

    // 填充backend
    for (i32 xx = 0; xx < GetFullSize(); ++xx)
    {
        for (i32 zz = 0; zz < GetFullSize(); ++zz)
        {
            glm::i32vec2 sswc = swc + glm::i32vec2{xx, zz};
            // 从缓存中查找
            Sp<Section> cache = BlockSystem::Instance()->GetSectionCache(sswc);
            if (cache)
            {
                sections[xx][zz] = cache;
            }
            else
            {
                // 生成新区块
                sections[xx][zz] = Section::NewObject<Section>();
                sections[xx][zz]->InitOpenGL();
                sections[xx][zz]->GenerateBlocks({swc.x + xx, swc.y + zz});
            }
        }
    }

    FreshBufferData();
}

void Lattice::RefreshCenter(glm::i32vec2 center_swc)
{
    glm::i32vec2 swc = {center_swc.x - GetFullSize() / 2, center_swc.y - GetFullSize() / 2};
    Refresh(swc);
}

void Lattice::FreshBufferData()
{
    for (u32 xx = 1; xx < GetFullSize() - 1; ++xx)
    {
        for (u32 zz = 1; zz < GetFullSize() - 1; ++zz)
        {
            sections[xx][zz]->FreshBufferData(*this);
        }
    }
}

Opt<Block> Lattice::GetBlock(glm::i32vec3 bwc)
{
    glm::i32vec2 lbwc = Get_swc();
    lbwc *= Section::Size;

    // 边界检查
    if (bwc.x < lbwc.x || bwc.x >= lbwc.x + GetFullSize() * Section::Size ||
        bwc.z < lbwc.y || bwc.z >= lbwc.y + GetFullSize() * Section::Size ||
        bwc.y < 0 || bwc.y >= Section::Height)
    {
        return nullopt;
    }

    glm::i32vec3 slc = {(bwc.x - lbwc.x) / Section::Size, 0, (bwc.z - lbwc.y) / Section::Size};
    glm::i32vec3 bsc = {(bwc.x - lbwc.x) % Section::Size, bwc.y, (bwc.z - lbwc.y) % Section::Size};
    auto section = sections[slc.x][slc.z];
    auto block = section->Blocks[bsc.x][bsc.y][bsc.z];
    return block;
}

void Lattice::Update(LatticeRenderCenter& lrc)
{
    glm::i32vec2 swc = lrc.Get_swc();

    // 中心区块坐标变化，刷新网格。
    if (swc != GetCenterSectionCor())
    {
        RefreshCenter(swc);
    }
}
