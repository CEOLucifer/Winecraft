#include "Transform.h"

glm::mat4 Transform::GetViewMat()
{
    glm::mat4 view;

    glm::vec3 lookDir = GetForward();
    glm::vec3 up = GetUp();

    view = glm::lookAt(position, position + lookDir, up);
    return view;
}

glm::vec3 Transform::GetForward()
{
    glm::vec3 forward;
    forward = GetRotateMat() * glm::vec4(0, 0, -1, 0);
    return forward;
}

glm::vec3 Transform::GetUp()
{
    glm::vec3 up;
    up = GetRotateMat() * glm::vec4(0, 1, 0, 0);
    return up;
}

glm::vec3 Transform::GetRight()
{
    glm::vec3 right;
    right = GetRotateMat() * glm::vec4(1, 0, 0, 0);
    return right;
}

glm::mat4 Transform::GetRotateMat()
{
    glm::mat4 rotate = {1};
    // 直接在一个矩阵上应用所有旋转
    rotate = glm::rotate(rotate, glm::radians(rotation.y),
                         glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(rotation.x),
                         glm::vec3(1.0f, 0.0f, 0.0f));
    rotate = glm::rotate(rotate, glm::radians(rotation.z),
                         glm::vec3(0.0f, 0.0f, 1.0f));
    return rotate;
}
