#include "Block/Lattice.h"
#include "Debug/Debug.h"

Lattice::Lattice()
{
    // Size * Size
    sections.resize(Size);
    for (auto& each: sections)
    {
        each.resize(Size);
        for (auto& section: each)
        {
            section = Section::Create();
        }
    }
}


void Lattice::Init(glm::i32vec2 swc)
{
    this->swc = swc;
    for (int xx = 0; xx < Lattice::Size; ++xx)
    {
        for (int zz = 0; zz < Lattice::Size; ++zz)
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
    for (int xa = 0; xa < Lattice::GetSize(); ++xa)
    {
        for (int za = 0; za < Lattice::GetSize(); ++za)
        {
            // 新网格中的坐标
            glm::i32vec2 slc = {old_swc.x + xa - swc.x, old_swc.y + za - swc.y};
            // 不在新网格中，添加到blandSections
            if (slc.x < 0 || slc.x >= Lattice::GetSize() ||
                slc.y < 0 || slc.y >= Lattice::GetSize())
            {
                blankSections.push_back(sections[xa][za]);
            }
        }
    }

    // 填充backend
    Vec backend(Section::GetSize(), Vec(Section::GetSize(), Sp<Section>()));
    for (int xa = 0; xa < Lattice::GetSize(); ++xa)
    {
        for (int za = 0; za < Lattice::GetSize(); ++za)
        {
            // 旧网格中的坐标
            glm::i32vec2 slc = {swc.x + xa - old_swc.x, swc.y + za - old_swc.y};
            if (0 <= slc.x && slc.x < Lattice::GetSize() &&
                0 <= slc.y && slc.y < Lattice::GetSize())
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
    glm::i32vec2 swc = {center_swc.x - GetSize() / 2, center_swc.y - GetSize() / 2};
    Refresh(swc);
}

bool Lattice::IsInited()
{
    return isInited;
}

void Lattice::FreshBufferData()
{
    for (int xx = 0; xx < Lattice::Size; ++xx)
    {
        for (int zz = 0; zz < Lattice::Size; ++zz)
        {
            sections[xx][zz]->FreshBufferData();
        }
    }
}

