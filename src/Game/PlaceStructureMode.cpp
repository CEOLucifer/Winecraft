#include "Game/PlaceStructureMode.hpp"
#include "Block/Structure.hpp"
#include "Block/StructureGenerator.h"
#include "Creature/Player.h"
#include "Debug/Debug.h"
#include "EMouseAction.hpp"
#include "EMouseButton.hpp"
#include "FileHelper.h"
#include "InputSystem.h"

void PlaceStructureMode::Enter() { Debug::Log("enter place structure mode"); }

void PlaceStructureMode::Exit(Player& player)
{
    player.ClearStructureMode();
    Debug::Log("exit place structure mode");
}

void PlaceStructureMode::Update(Player& player)
{
    if (Input::GetMouse(EMouseButton::Left, EMouseAction::Down))
    {
        auto jsonStr = FileHelper::ReadFile("save/1.json");
        Structure structure;
        structure.Deserialize(jsonStr);

        auto block = player.GetStaredEmptyBlock();
        if (block)
        {
            StructureGenerator::CreateStructure(structure, *block);
        }
    }
}