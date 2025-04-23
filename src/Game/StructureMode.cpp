#include "Game/StructureMode.hpp"
#include "Block/BlockSystem.h"
#include "Debug/Debug.h"
#include "FileHelper.h"
#include "InputSystem.h"
#include "Creature/Player.h"

void StructureMode::Enter() { Debug::Log("Enter Structure Mode"); }

void StructureMode::SetCor0(i32vec3 value)
{
    selectedCor0 = value;
    Debug::Log("SetCor0");
}

void StructureMode::SetCor1(i32vec3 value)
{
    selectedCor1 = value;
    Debug::Log("SetCor1");
}

void StructureMode::CreateStructure()
{
    i32vec3 cor0;
    cor0.x = std::min(selectedCor0.x, selectedCor1.x);
    cor0.y = std::min(selectedCor0.y, selectedCor1.y);
    cor0.z = std::min(selectedCor0.z, selectedCor1.z);

    i32vec3 cor1;
    cor1.x = std::max(selectedCor0.x, selectedCor1.x);
    cor1.y = std::max(selectedCor0.y, selectedCor1.y);
    cor1.z = std::max(selectedCor0.z, selectedCor1.z);

    i32vec3 dimension = {cor1.x - cor0.x + 1, cor1.y - cor0.y + 1,
                         cor1.z - cor0.z + 1};
    structure.SetSize(dimension.x, dimension.y, dimension.z);
    for (i32 x = 0; x < dimension.x; ++x)
    {
        for (i32 y = 0; y < dimension.y; ++y)
        {
            for (i32 z = 0; z < dimension.z; ++z)
            {
                auto block =
                    BlockSystem::Instance()->GetBlock(cor0 + i32vec3{x, y, z});
                if (block)
                {
                    structure[x, y, z] = *block;
                }
            }
        }
    }

    Debug::Log("CreateStructure");
}

void StructureMode::SaveStructure()
{
    String jsonStr = structure.Serialize();
    FileHelper::WriteFile(savePath, jsonStr);

    Debug::Log("SaveStructure");
}

void StructureMode::Update(Player& player)
{
    if (Input::GetMouse(EMouseButton::Left, EMouseAction::Down))
    {
        if (stage == 0)
        {
            auto info = player.GetStaredBlock();
            if (info.block)
            {
                SetCor0(info.bwc);
                ++stage;
            }
        }
        else if (stage == 1)
        {
            auto info = player.GetStaredBlock();
            if (info.block)
            {
                SetCor1(info.bwc);
                ++stage;
            }
        }
        else if (stage == 2)
        {
            CreateStructure();
            SetSavePath("save/1.json");
            SaveStructure();
            Exit(player);
        }
    }
}

void StructureMode::Exit(Player& player)
{
    player.ClearStructureMode();
    Debug::Log("Exit Structure Mode");
}
