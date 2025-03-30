#include "Block/Lattice.h"
#include "Debug/Debug.h"
#include "Block/LatticeRenderCenter.h"

using namespace std;

void Lattice::Init(u32 renderSize, glm::i32vec2 swc)
{
    if ((renderSize & 1) == 0)
    {
        Debug::LogError("renderSize必须是奇数");
    }

    // 创建空Sections
    u32 fullSize = renderSize + 2;
    sections.resize(fullSize);
    for (auto& each: sections)
    {
        each.resize(fullSize);
        for (auto& section: each)
        {
            section = Section::Create();
            section->InitOpenGL();
        }
    }

    this->swc = swc;
    for (u32 xx = 0; xx < GetFullSize(); ++xx)
    {
        for (u32 zz = 0; zz < GetFullSize(); ++zz)
        {
            sections[xx][zz]->GenerateBlocks({swc.x + xx, swc.y + zz});
        }
    }
    FreshBufferData();

    isInited = true;
}

void Lattice::Refresh(glm::i32vec2 swc)
{
    if (!isInited)
    {
        Debug::LogError("Lattice must be init before refresh!");
        return;
    }

    if (this->swc == swc)
    {
        return;
    }

    glm::i32vec2 old_swc = this->swc;

    // 收集blankSections：不会出现在新网格中的原区块
    Vec<Sp<Section>> blankSections;
    for (int xa = 0; xa < GetFullSize(); ++xa)
    {
        for (int za = 0; za < GetFullSize(); ++za)
        {
            // 新网格中的坐标
            glm::i32vec2 slc = {old_swc.x + xa - swc.x, old_swc.y + za - swc.y};
            // 不在新网格中，添加到blandSections
            if (slc.x < 0 || slc.x >= GetFullSize() ||
                slc.y < 0 || slc.y >= GetFullSize())
            {
                blankSections.push_back(sections[xa][za]);
            }
        }
    }

    // 填充backend
    Vec backend(GetFullSize(), Vec(GetFullSize(), Sp<Section>()));
    for (int xa = 0; xa < GetFullSize(); ++xa)
    {
        for (int za = 0; za < GetFullSize(); ++za)
        {
            // 旧网格中的坐标
            glm::i32vec2 slc = {swc.x + xa - old_swc.x, swc.y + za - old_swc.y};
            if (0 <= slc.x && slc.x < GetFullSize() &&
                0 <= slc.y && slc.y < GetFullSize())
            {
                // 在旧网格中，赋值过来
                backend[xa][za] = sections[slc.x][slc.y];
            }
            else
            {
                // 不在，从blankSections中借一个
                backend[xa][za] = blankSections.back();
                blankSections.pop_back();
                backend[xa][za]->GenerateBlocks({swc.x + xa, swc.y + za});
            }
        }
    }

    sections = std::move(backend);
    this->swc = swc;
    FreshBufferData();
}

void Lattice::RefreshCenter(glm::i32vec2 center_swc)
{
    glm::i32vec2 swc = {center_swc.x - GetFullSize() / 2, center_swc.y - GetFullSize() / 2};
    Refresh(swc);
}

bool Lattice::IsInited()
{
    return isInited;
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
