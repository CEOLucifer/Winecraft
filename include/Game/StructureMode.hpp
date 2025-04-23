#pragma once

#include "Block/Structure.hpp"
#include "Mode.hpp"
#include "Std/Math.h"
#include "Std/String.h"

class Player;

/// @brief 结构模式
class StructureMode : public Mode
{
private:
    i32vec3 selectedCor0;
    i32vec3 selectedCor1;

    Structure structure;
    String savePath;

    int stage = 0;

public:
    void Enter() override;

    void SetCor0(i32vec3 value);

    void SetCor1(i32vec3 value);

    void CreateStructure();

    void SetSavePath(const String& value) { savePath = value; }

    void SaveStructure();

    void Exit(Player& player) override;

    void Update(Player& player) override;
};