#include "Core/Branch.h"

void Branch::SetPosition(vec3 value)
{
    vec3 delta = value - Position;
    Position = value;
    for(auto each : childBranches)
    {
        vec3 oldPos = each->Position;
        each->SetPosition(oldPos + delta);
    }
}

void Branch::_callOnNodeDestroyedOfChildren()
{
    for (auto each: childNodes)
    {
        each->OnNodeDestroyed();
    }

    for (auto each: childBranches)
    {
        each->OnNodeDestroyed();
    }

    for (auto each: childBranches)
    {
        each->_callOnNodeDestroyedOfChildren();
    }
}