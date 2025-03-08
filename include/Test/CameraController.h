#pragma once

#include "../Core/Node.h"
#include "../Typedef.h"

class Camera;

class CameraController : public Node
{
public:
    Sp<Camera> camera;
    float cameraSpeed = 3;
    float cursorSpeed = 0.2;


public:
    void Update() override;
};