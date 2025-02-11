#include "Update/UpdateSystem.h"
#include "Update/Updatable.h"

void UpdateSystem::Update(float deltaTime)
{
    for (auto each : updateVec)
    {
        each->Update(deltaTime);
    }
}

void UpdateSystem::Add(std::shared_ptr<Updatable> updatable)
{
    updateVec.push_back(updatable);
}

void UpdateSystem::Remove(std::shared_ptr<Updatable> updatable)
{
    for (auto each = updateVec.begin(); each != updateVec.end(); each++)
    {
        if (*each == updatable)
        {
            updateVec.erase(each);
            break;
        }
    }
}
