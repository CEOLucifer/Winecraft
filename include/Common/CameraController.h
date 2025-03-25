#pragma once


#include "Core/Node.h"

class Camera;

class CameraController : public Node
{
public:
    Sp<Camera> camera;
    float cameraSpeed = 10;
    float cursorSpeed = 0.15;

public:
    void OnAdded() override;

    void Update() override;
};