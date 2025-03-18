#pragma once

#include "Singleton.h"
#include "Aggre/Vec.h"
#include "Block/Section.h"
#include <glm/glm.hpp>
#include "Typedef.h"
#include "Std/Opt.h"
#include "Std/Basic.h"


class SectionsCenter;

/// 方块系统。管理区块的存储，生成，区块动态增删等等。
class BlockSystem : public Singleton<BlockSystem>
{
    friend class BlockRenderPass;

public:
    static constexpr u32 Size = 3;

private:
    Vec<Vec<Section>> sections;

    glm::i32vec3 systemCoords = {0, 0, 0};

    Sp<SectionsCenter> sectionsCenter;


public:
    void OnLoad() override;

    /// 获取区块的长宽数
    u32 GetSize()
    {
        return Size;
    }

    /// 系统（左下角）的世界坐标
    glm::i32vec3 GetSystemCoords()
    {
        return systemCoords;
    }

    /// 系统中心区块的世界坐标
    glm::vec3 GetCenterCoords();

    /// 获取指定世界坐标的区块
    Opt<Block> GetBlock(glm::i32vec3 worldCoords);

    void SetSectionsCenter(Sp<SectionsCenter> value)
    {
        sectionsCenter = value;
    }


private:
    /// 初始化sections，设置区块数量
    void initSectionsSize();

    /// 柏林噪声
    void generateRandom_Berlin();

    /// Value噪声
    void generateRandom_Value();

    void generateRandom_Value2();

    /// 更新区块，动态加载和卸载区块
    void updateSections();
};