#include "Block/SectionsCenter.h"
#include "Block/BlockSystem.h"

void SectionsCenter::Awake()
{
    BlockSystem::Instance()->SetSectionsCenter(CastTo<SectionsCenter>());
}