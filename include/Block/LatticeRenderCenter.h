#pragma once

#include "Core/Node.h"
#include <glm/glm.hpp>

/// 区块加载的中心点。一般情况下，挂载于玩家摄像机。
class LatticeRenderCenter : public Node
{
public:
    void OnAdded() override;

    // 所在的区块的区块世界坐标
    glm::i32vec2 Get_swc();
};