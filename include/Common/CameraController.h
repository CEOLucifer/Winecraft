#pragma once


#include "Core/Node.h"

class Camera;

class CameraController : public Node
{
public:
    Sp<Camera> camera;
    float cameraSpeed = 10;
    float cursorSpeed = 0.15;

private:
    bool isEnableMove = true;

public:
    void OnAdded() override;

    void Update() override;

    void SetIsEnableMove(bool value)
    {
        isEnableMove = value;
    }
};