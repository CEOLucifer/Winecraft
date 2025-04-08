#pragma once

#include "Block.h"
#include "Std/Array.h"
#include <glm/glm.hpp>
#include "Std/SmartPtr.h"
#include "Std/Vec.h"
#include "Core/Object.h"
#include "Std/Math.h"

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
    /// 区块世界坐标
    i32vec2 swc = {0, 0};

public:
    Section();

    ~Section();

    i32vec2 Get_swc()
    {
        return swc;
    }

    /// ！！！通过调用此函数设置区块世界坐标，才能调用生成函数
    void Set_swc(i32vec2 value);


#pragma region 生成
private:
    bool isFull = false;

public:
    void FillWith(Block block);

    void Clear()
    {
        FillWith(0);
    }

    bool GetIsFull()
    {
        return isFull;
    }

    // 以下函数，是按照阶段顺序编写。

    /// 生成基本地形。基于Value噪声。
    void GenerateBase();

    /// 生成树木
    void GenerateTree();

    void GenerateFull();

#pragma endregion


#pragma region 渲染
private:
    u32 vao = 0;

    u32 aModelsVbo = 0;

    /// 存储方块的model
    Vec<glm::mat4> aModels = {};

    u32 aTexIndsVbo = 0;

    /// 存储方块的texInd
    Vec<u32> aTexInds = {};

    u32 aDataVbo = 0;

    Vec<vec4> aDatas = {};

    bool isOpenGLInited = false;

    bool isFreshBufferData = false;

public:
    /// 初始化opengl相关。！！！需要在new Section后调用。
    void InitOpenGL();

    void ClearOpenGL();

    u32 GetVao()
    {
        return vao;
    }

    /// 根据当前方块数据，更新BufferData
    void FreshBufferData();


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

    bool GetIsOpenGLInited()
    {
        return isOpenGLInited;
    }

    bool GetIsFreshBufferData()
    {
        return isFreshBufferData;
    }

private:
    static u32 blockVerticeVbo;
    static u32 blockVerticeEbo;
    static Vec<u32> indices;

public:
    static void Load();

    static void Unload();

#pragma endregion


#pragma region 序列化
#pragma endregion


public:
    static Sp<Section> NewSection()
    {
        return Object::NewObject<Section>();
    }

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