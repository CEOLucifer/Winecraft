#pragma once

#include "Std/Vec.h"
#include "Section.h"

/// 网格
class Lattice
{
public:
    // 区块的长宽数，规定：奇数。
    static constexpr i32 Size = 7;

private:
    Vec<Vec<Sp<Section>>> sections;

    /// 坐标。单位：区块；相对：世界
    glm::i32vec2 swc = {0, 0};

    bool isInited = false;

public:
    Lattice();

    /// 初始化，必须先由外部调用，然后才能调用Refresh
    /// \param swc
    void Init(glm::i32vec2 swc);

    glm::i32vec2 GetCenterSectionCor()
    {
        return {swc.x + Lattice::Size / 2, swc.y + Lattice::Size / 2};
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

    void RefreshCenter(glm::i32vec2 center_swc);

    Vec<Vec<Sp<Section>>>& GetSections()
    {
        return sections;
    };

    bool IsInited();

    /// 刷新每个区块的BufferData
    void FreshBufferData();

public:
    static constexpr i32 GetSize()
    {
        return Size;
    }
};