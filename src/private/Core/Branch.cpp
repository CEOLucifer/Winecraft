#include "Core/Branch.h"
#include "Core/CoreSystem.h"

void Branch::_callOnDestroyedOfChildren()
{
    for (auto each : childNodes)
    {
        each->OnDestroyed();
    }

    for (auto each : childBranches)
    {
        each->OnDestroyed();
    }

    for (auto each : childBranches)
    {
        each->_callOnDestroyedOfChildren();
    }
}