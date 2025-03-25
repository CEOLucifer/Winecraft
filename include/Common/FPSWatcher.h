#pragma once

#include "Core/Branch.h"

class Label;

class FPSWatcher : public Node
{
private:
    Sp<Label> lab;

    f32 freshInterval = 1.0;
    f32 freshTimer = 0.0;

    u32 frameCount = 0;
    f32 lastRunTime = 0.0;

public:
    void OnAdded() override;

    void Update() override;
};