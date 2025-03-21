#pragma once

#include "Singleton.h"
#include "Std/Vec.h"
#include "Block/Section.h"
#include <glm/glm.hpp>
#include "Std/SmartPtr.h"
#include "Std/Opt.h"
#include "Std/Basic.h"
#include "Lattice.h"


class LatticeRenderCenter;

/// 方块系统。管理区块的存储，生成，区块动态增删等等。
class BlockSystem : public Singleton<BlockSystem>
{
    friend class BlockRenderPass;

private:
    /// 两个网格。动态加载地图时，在两个之中来回切换，分为前后端网格。
    Lattice latticeAB[2];

    /// 前端网格索引
    u32 frontLatticeInd = 0;

    Sp<LatticeRenderCenter> latticeCenter;


public:
    void OnLoad() override;

    /// 获取指定世界坐标的区块
    Opt<Block> GetBlock(glm::i32vec3 worldCor);

    void SetSectionsCenter(Sp<LatticeRenderCenter> value)
    {
        latticeCenter = value;
    }

private:
    /// 初始化sections，设置区块数量
    void initSectionsSize();

    /// 当前的网格
    Lattice& getFrontLattice()
    {
        return latticeAB[frontLatticeInd];
    }

    Lattice& getBackLattice()
    {
        return latticeAB[(frontLatticeInd + 1) % 2];
    }

    /// 更新网格，动态加载和卸载区块
    void updateLattice();
};