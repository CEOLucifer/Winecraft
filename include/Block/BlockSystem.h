#pragma once

#include "Singleton.h"
#include <vector>
#include "Block/Section.h"
#include <glm/glm.hpp>
#include <optional>

class BlockSystem : public Singleton<BlockSystem>
{
    friend class BlockRenderPass;

public:
    static constexpr uint32_t Size = 6;

private:
    std::vector<std::vector<Section>> sections;

    glm::i32vec3 systemCoords = {0, 0, 0};


public:
    void OnLoad() override;

    /// 获取区块的长宽数
    uint32_t GetSize()
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
    std::optional<Block> GetBlock(glm::i32vec3 worldCoords);


private:
    /// 初始化sections，设置区块数量
    void initSectionsSize();

    /// 柏林噪声
    void generateRandom_Berlin();

    /// Value噪声
    void generateRandom_Value();
};