#pragma once

#include "Block.h"
#include "Std/Array.h"
#include <glm/glm.hpp>
#include "Std/SmartPtr.h"
#include "Std/Vec.h"
#include "Core/Object.h"

class Lattice;

/// 区块
class Section : public Object
{
public:
    static constexpr i32 Size = 16;
    static constexpr i32 Height = 96;

public:
    Array<Array<Array<Block, Size>, Height>, Size> Blocks = {};

private:
    u32 vao = 0;

    u32 aModelsVbo = 0;

    /// 存储方块的model
    Vec<glm::mat4> aModels = {};

    u32 aTexIndsVbo = 0;

    /// 存储方块的texInd
    Vec<u32> aTexInds = {};

    /// 区块世界坐标
    glm::i32vec2 swc = {};

public:
    Section();

    ~Section();

    /// 初始化opengl相关
    void InitOpenGL();

    void ClearOpenGL();

    u32 GetVao()
    {
        return vao;
    }

    void FillWith(Block block);

    void Clear()
    {
        FillWith(0);
    }

    /// 生成方块数据
    void GenerateBlocks(glm::i32vec2 swc);

    /// 根据当前方块数据，更新BufferData
    void FreshBufferData(Lattice& lattice);

    u32 GetaModelsVbo()
    {
        return aModelsVbo;
    }

    Vec<glm::mat4>& GetaModels()
    {
        return aModels;
    }

    u32 GetaTexIndsVbo()
    {
        return aTexIndsVbo;
    }

    glm::i32vec2 Get_swc()
    {
        return swc;
    }

    void SaveSection();

    void LoadSection();

private:
    /// Value噪声
    void generateRandom_Value(glm::i32vec2 swc);

    /// 柏林噪声
    void generateRandom_Berlin(glm::i32vec2 swc);

private:
    static u32 blockVerticeVbo;
    static u32 blockVerticeEbo;
    static Vec<u32> indices;

public:
    static void Load();

    static void Unload();

    static constexpr i32 GetSize()
    {
        return Size;
    }

    static constexpr i32 GetHeight()
    {
        return Height;
    }

    static Vec<u32>& GetIndices()
    {
        return indices;
    }
};