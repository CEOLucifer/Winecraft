#pragma once

#include "Transform.h"

class Camera : public Transform
{
private:
    float width = 800;
    float height = 600;
    float near = 0.1f;
    float far = 100.0f;
    float fov = 45.0f;

public:
    float GetWidth() { return width; }
    float GetHeight() { return height; }
    float GetAspect() { return width / height; }
    float GetNear() { return near; }
    float GetFar() { return far; }
    float GetFov() { return fov; }
};