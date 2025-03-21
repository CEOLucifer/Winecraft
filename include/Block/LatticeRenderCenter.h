#pragma once

#include "Core/Node.h"

/// 区块加载的中心点。一般情况下，挂载于玩家。
class LatticeRenderCenter : public Node
{
public:
    void Awake() override;
};