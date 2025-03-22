#include "Block/LatticeRenderCenter.h"
#include "Block/BlockSystem.h"
#include "Core/Branch.h"

void LatticeRenderCenter::OnAdded()
{
    BlockSystem::Instance()->SetLatticeRenderCenter(CastTo<LatticeRenderCenter>());
}

glm::i32vec2 LatticeRenderCenter::Get_swc()
{
    glm::vec3 pos = GetParent().lock()->Position;
    glm::i32vec2 swc = {floor(pos.x / Section::GetSize()), floor(pos.z / Section::GetSize())};
    return swc;
}
