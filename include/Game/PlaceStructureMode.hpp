#pragma once

#include "Mode.hpp"

class Player;

class PlaceStructureMode : public Mode
{
public:
    void Enter() override;

    void Exit(Player& player) override;

    void Update(Player& player) override;
};