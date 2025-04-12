#pragma once

#include "Common/SingletonNode.h"

class Player;
class Image;

class GameSystem : public SingletonNode<GameSystem>
{
private:
    Sp<Player> player;

    Sp<Branch> aimerBra;

    Sp<Image> aimer;

public:
    void SetPlayer(Sp<Player> value)
    {
        player = value;
    }

    Player& GetPlayer()
    {
        return *player;
    }

    void Awake() override;

    void Update() override;
};