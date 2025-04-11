#pragma once

#include "Core/Node.h"
#include "Std/Math.h"

/// 刚体节点
class Rigidbody : public Node
{
private:
    f32 g = -20;

    vec3 velocity = {0, 0, 0};

public:
    void Set_g(f32 value)
    {
        g = value;
    }

    void Update() override;

    void SetVelocity(vec3 value)
    {
        velocity = value;
    }

    vec3 GetVelocity()
    {
        return velocity;
    }

private:
    void updatePhysics();
};