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
    static constexpr u32 Size = 16;
    static constexpr u32 Height = 128;

public:
    Array<Array<Array<Block, Size>, Height>, Size> Blocks = {};

private:
    u32 aModelsVbo = 0;

    /// 存储方块的model
    Vec<glm::mat4> aModels = {};

    /// 世界区块坐标
    glm::i32vec2 cor = {};

public:
    Section();

    ~Section();

    void FillWith(Block block);

    void Clear()
    {
        FillWith(0);
    }

    void GenerateRandom(glm::i32vec2 sectionCor);

    void TransferBufferData();

    u32 GetaModelsVbo()
    {
        return aModelsVbo;
    }

    Vec<glm::mat4>& GetaModels()
    {
        return aModels;
    }


private:
    /// Value噪声
    void generateRandom_Value(glm::i32vec2 sectionCor);

    /// 柏林噪声
    void generateRandom_Berlin(glm::i32vec2 sectionCor);

public:
    static Sp<Section> Create();

    static constexpr u32 GetSize()
    {
        return Size;
    }

    static constexpr u32 GetHeight()
    {
        return Height;
    }
};