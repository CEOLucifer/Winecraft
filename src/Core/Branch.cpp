#include "Core/Branch.h"
#include "Core/CoreSystem.h"

void Branch::_callOnNodeDestroyedOfChildren()
{
    for (auto each : childNodes)
    {
        each->OnNodeDestroyed();
    }

    for (auto each : childBranches)
    {
        each->OnNodeDestroyed();
    }

    for (auto each : childBranches)
    {
        each->_callOnNodeDestroyedOfChildren();
    }
}