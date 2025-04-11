#pragma once

#include "Creature.h"

class Rigidbody;

class Player : public Creature
{
private:
    f32 walkSpeed = 8;

    Sp<Branch> cameraBra;

    Sp<Rigidbody> rigidbody;

public:
    void Awake() override;

    void Update() override;
};
