#pragma once

#include "Singleton.h"
#include <vector>
#include "Block/Section.h"

class BlockSystem : public Singleton<BlockSystem>
{
    friend class BlockRenderPass;

private:
    std::vector<std::vector<Section>> sections;

public:
    void OnLoad() override;

private:
    void initSections();
};