#pragma once

#include "Singleton.h"
#include "Std/Vec.h"
#include "Block/Section.h"
#include <glm/glm.hpp>
#include "Std/SmartPtr.h"
#include "Std/Opt.h"
#include "Std/Basic.h"
#include "Lattice.h"
#include "Std/Map.h"
#include "Std/Hash.h"

class LatticeRenderCenter;

/// 方块系统。管理区块的存储，生成，区块动态增删等等。
class BlockSystem : public Singleton<BlockSystem>
{
    friend class BlockRenderPass;

private:
    Lattice lattice;

    Sp<LatticeRenderCenter> latticeRenderCenter;

    /// 区块缓存
    Map<i32vec2, Sp<Section>> sectionCaches;


public:
    void OnLoad() override;

    void SetLatticeRenderCenter(Sp<LatticeRenderCenter> value);

    Sp<LatticeRenderCenter> GetLatticeRenderCenter()
    {
        return latticeRenderCenter;
    }

    Lattice& GetLattice()
    {
        return lattice;
    }

    void Update();

    void CacheSection(Sp<Section> section);

    /// 获取区块缓存。指定的坐标的区块是已生成好的，但是OpenGL相关未初始化。
    /// \param swc
    /// \return
    Sp<Section> GetSectionCache(glm::i32vec2 swc);

    bool IsCachedSection(glm::i32vec2 swc)
    {
        return GetSectionCache(swc) != nullptr;
    }

    void RemoveSectionCache(i32vec2 swc);

    /// 获取指定世界坐标的区块
    Opt<Block> GetBlock(glm::i32vec3 bwc);

    void SetBlock(Block block, i32vec3 bwc);
};