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
    Lattice lattice;

    Sp<LatticeRenderCenter> latticeRenderCenter;


public:
    void OnLoad() override;

    /// 获取指定世界坐标的区块
    Opt<Block> GetBlock(glm::i32vec3 bwc);

    void SetLatticeRenderCenter(Sp<LatticeRenderCenter> value);

    Lattice& GetLattice()
    {
        return lattice;
    }

    void Update();
};