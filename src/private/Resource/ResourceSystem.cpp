#include "Resource/ResourceSystem.h"
#include "Resource/Resource.h"

void ResourceSystem::Cache(std::shared_ptr<Resource> res)
{
    resMap.insert({res->GetPath(), res});
}