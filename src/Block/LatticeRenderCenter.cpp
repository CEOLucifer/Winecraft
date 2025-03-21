#include "Block/LatticeRenderCenter.h"
#include "Block/BlockSystem.h"

void LatticeRenderCenter::Awake()
{
    BlockSystem::Instance()->SetSectionsCenter(CastTo<LatticeRenderCenter>());
}