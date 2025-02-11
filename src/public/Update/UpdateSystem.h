#pragma once

#include <memory>
#include <vector>
#include "Singleton.h"

class Updatable;

class UpdateSystem : public Singleton<UpdateSystem>
{
private:
    std::vector<std::shared_ptr<Updatable>> updateVec;

public:
    void Update(float deltaTime);

    void Add(std::shared_ptr<Updatable> updatable);

    void Remove(std::shared_ptr<Updatable> updatable);
};