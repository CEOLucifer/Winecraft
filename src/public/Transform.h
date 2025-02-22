#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/// @brief 变换
/// 
class Transform
{
public:
    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};
    glm::vec3 scale = {1, 1, 1};

public:
    glm::vec3 GetForward();

    glm::vec3 GetUp();

    glm::vec3 GetRight();

    glm::mat4 GetRotateMat();

    glm::mat4 GetViewMat();

    glm::mat4 GetModelMat();
};