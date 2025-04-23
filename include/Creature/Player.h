#pragma once

#include "Creature.h"
#include "Block/Block.h"
#include "Std/Opt.h"
#include "Game/StaredBlockInfo.h"

class Rigidbody;
class Mode;

class Player : public Creature
{
private:
    f32 walkSpeed = 8;

    Sp<Branch> cameraBra;

    Sp<Rigidbody> rigidbody;

    f32 reachBlockDistance = 1000;

    Sp<Mode> mode = nullptr;

public:
    void Awake() override;

    void Update() override;

    StaredBlockInfo GetStaredBlock();

    Opt<i32vec3> GetStaredEmptyBlock();

    void ClearStructureMode() { mode = nullptr; }

    void EnterMode(Sp<Mode> _mode);
};
