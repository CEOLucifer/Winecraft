#pragma once


#include "Core/Branch.h"

class TestNode : public Branch
{
public:
    void Awake() override;

    void Update() override;
};