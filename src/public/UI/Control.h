#pragma once

#include "Node/ParentNode2D.h"

/// @brief 控件基类
class Control : public ParentNode2D
{
public:
    glm::vec2 Size;

public:
    virtual void Draw();
};