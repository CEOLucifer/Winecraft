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
            sections[xx][zz] = Section::NewSection();
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
                Sp<Section> section = Section::NewObject<Section>();
                sections[xx][zz] = section;
                section->Set_swc({swc.x + xx, swc.y + zz});
            }
        }
    }
}

void Lattice::RefreshCenter(glm::i32vec2 center_swc)
{
    glm::i32vec2 swc = {center_swc.x - GetFullSize() / 2, center_swc.y - GetFullSize() / 2};
    Refresh(swc);
}

void Lattice::FreshBufferData()
{
    // 只有渲染区域的区块才调用
    for (u32 xx = 1; xx < GetFullSize() - 1; ++xx)
    {
        for (u32 zz = 1; zz < GetFullSize() - 1; ++zz)
        {
            if (!sections[xx][zz]->GetIsOpenGLInited())
            {
                sections[xx][zz]->InitOpenGL();
            }
            sections[xx][zz]->FreshBufferData();
        }
    }
}

void Lattice::Update(LatticeRenderCenter& lrc)
{
    glm::i32vec2 swc = lrc.Get_swc();

    // 中心区块坐标变化，刷新网格。
    if (swc != GetCenterSectionCor())
    {
        RefreshCenter(swc);
    }

    for (u32 xx = 0; xx < GetFullSize(); ++xx)
    {
        for (u32 zz = 0; zz < GetFullSize(); ++zz)
        {
            Sp<Section> section = sections[xx][zz];

            if (!section->GetIsOpenGLInited())
            {
                section->InitOpenGL();
            }

            if(!section->GetIsFull())
            {
                section->GenerateFull();
            }
        }
    }

    for (u32 xx = 0; xx < GetFullSize(); ++xx)
    {
        for (u32 zz = 0; zz < GetFullSize(); ++zz)
        {
            Sp<Section> section = sections[xx][zz];

            if(!section->GetIsFreshBufferData())
            {
                section->FreshBufferData();
            }
        }
    }
}

