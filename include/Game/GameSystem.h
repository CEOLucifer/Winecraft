#pragma once

#include "Common/SingletonNode.h"

class Player;

class GameSystem : public SingletonNode<GameSystem>
{
private:
    Sp<Player> player;

public:
    void SetPlayer(Sp<Player> value)
    {
        player = value;
    }

    Player& GetPlayer()
    {
        return *player;
    }
};