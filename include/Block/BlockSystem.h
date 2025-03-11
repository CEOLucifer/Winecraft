#pragma once

#include "Singleton.h"
#include <vector>
#include "Block/Section.h"

class BlockSystem : public Singleton<BlockSystem>
{
    friend class BlockRenderPass;

public:
    static constexpr uint32_t Size = 10;

private:
    std::vector<std::vector<Section>> sections;

public:
    void OnLoad() override;

private:
    /// 初始化sections，设置区块数量
    void initSectionsSize();

    /// 柏林噪声
    void generateRandom_Berlin();

    /// 双线性插值
    void generateRandom_Bilinear();
};