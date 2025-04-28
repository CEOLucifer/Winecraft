#pragma once

#include "Creature.h"
#include "Block/Block.h"
#include "Std/Opt.h"
#include "Game/StaredBlockInfo.h"

class Rigidbody;
class Mode;
class FrameRenderPass;

class Player : public Creature
{
private:
    f32 walkSpeed = 8;

    Sp<Branch> cameraBra;

    Sp<Rigidbody> rigidbody;

    f32 reachBlockDistance = 10;

    Sp<Mode> mode = nullptr;

    Sp<FrameRenderPass> frameRenderPass;

public:
    void Awake() override;

    void Update() override;

    StaredBlockInfo GetStaredBlock();

    Opt<i32vec3> GetStaredEmptyBlock();

    void ClearStructureMode() { mode = nullptr; }

    void EnterMode(Sp<Mode> _mode);

    Sp<Branch> GetCameraBra() { return cameraBra; }
};
