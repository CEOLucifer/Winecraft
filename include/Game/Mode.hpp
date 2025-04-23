#pragma once

class Player;

class Mode
{
public:
    virtual void Enter() {};

    virtual void Exit(Player& player) {};

    virtual void Update(Player& player) {};
};