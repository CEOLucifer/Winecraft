#pragma once

#include "glm/glm.hpp"

/// @brief 变换
class Transform
{
public:
    glm::vec3 Position = {0, 0, 0};
    glm::vec3 Rotation = {0, 0, 0};
    glm::vec3 Scale = {1, 1, 1};

public:
    glm::vec3 GetForward();

    glm::vec3 GetUp();

    glm::vec3 GetRight();

    glm::mat4 GetRotateMat();

    glm::mat4 GetViewMat();

    glm::mat4 GetModelMat();
};