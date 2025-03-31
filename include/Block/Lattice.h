#pragma once

#include "Std/Vec.h"
#include "Section.h"
#include "Std/Opt.h"

class BlockSystem;
class LatticeRenderCenter;

/// 网格
class Lattice
{
private:
    Vec<Vec<Sp<Section>>> sections;

    /// 坐标。单位：区块。相对：世界
    glm::i32vec2 swc = {0, 0};

public:
    /// 初始化，必须先由外部调用，然后才能调用Refresh
    /// \param renderSize 规定：奇数
    void Init(u32 renderSize);

    glm::i32vec2 GetCenterSectionCor()
    {
        return {swc.x + GetFullSize() / 2, swc.y + GetFullSize() / 2};
    }

    glm::i32vec2 Get_swc()
    {
        return swc;
    }

    void Set_swc(glm::i32vec2 value)
    {
        swc = value;
    }

    /// 刷新网格，动态加载和卸载区块。必须在Init之后调用。
    /// \param swc 网格的区块世界坐标
    void Refresh(glm::i32vec2 swc);

    /// 刷新网格，以中心区块坐标。
    /// \param center_swc
    void RefreshCenter(glm::i32vec2 center_swc);

    Vec<Vec<Sp<Section>>>& GetSections()
    {
        return sections;
    };

    /// 刷新所有渲染区块的BufferData
    void FreshBufferData();

    i32 GetFullSize()
    {
        return sections.size();
    }

    i32 GetRenderSize()
    {
        return sections.size() - 2;
    }

    /// 获取指定世界坐标的区块
    Opt<Block> GetBlock(glm::i32vec3 bwc);

    void Update(LatticeRenderCenter& lrc);
};