#pragma once

#include "Block.h"
#include "Std/Array.h"
#include <glm/glm.hpp>
#include "Std/SmartPtr.h"
#include "Std/Vec.h"

/// 区块
class Section
{
public:
    static constexpr i32 Size = 16;
    static constexpr i32 Height = 96;

public:
    Array<Array<Array<Block, Size>, Height>, Size> Blocks = {};

private:
    u32 aModelsVbo = 0;

    /// 存储方块的model
    Vec<glm::mat4> aModels = {};

    /// 区块世界坐标
    glm::i32vec2 swc = {};

public:
    Section();

    ~Section();

    void FillWith(Block block);

    void Clear()
    {
        FillWith(0);
    }

    /// 生成方块数据
    void GenerateBlocks(glm::i32vec2 swc);

    /// 根据当前方块数据，输送数据到显存
    void TransferBufferData();

    u32 GetaModelsVbo()
    {
        return aModelsVbo;
    }

    Vec<glm::mat4>& GetaModels()
    {
        return aModels;
    }

    /// 生成方块和显存数据
    /// \param swc
    void Refresh(glm::i32vec2 swc);

    glm::i32vec2 Get_swc()
    {
        return swc;
    }

private:
    /// Value噪声
    void generateRandom_Value(glm::i32vec2 swc);

    /// 柏林噪声
    void generateRandom_Berlin(glm::i32vec2 swc);

public:
    static Sp<Section> Create();

    static constexpr i32 GetSize()
    {
        return Size;
    }

    static constexpr i32 GetHeight()
    {
        return Height;
    }
};