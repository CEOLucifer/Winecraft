#pragma once

#include "Core/Node.h"
#include "glm/glm.hpp"

/// @brief 控件基类
class Control : public Node
{
public:
    /// @brief 宽高 
    glm::vec2 GetSize();

    void SetSize(glm::vec2 value);

    glm::vec2 GetPos();
};