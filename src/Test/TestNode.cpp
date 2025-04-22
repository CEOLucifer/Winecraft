#include "Test/TestNode.h"
#include "Block/BlockSystem.h"
#include "Block/Section.h"
#include "Block/Structure.hpp"
#include "FileHelper.h"
#include "Game/GameSystem.h"
#include "Creature/Player.h"
#include "Debug/Debug.h"
#include "Input/MouseButton.hpp"
#include "InputSystem.h"
#include "Std/Basic.h"
#include "Std/Map.h"
#include "Std/Hash.hpp"
#include <GLFW/glfw3.h>
#include "Block/BlockSystem.h"

void TestNode::Awake()
{
}

void TestNode::Update()
{
    if (Input::GetKey(GLFW_KEY_C, GLFW_PRESS))
    {
        static bool yes = false;

        if (!yes)
        {
            yes = true;

            BlockSystem::Instance()->PrintAllSwc();
        }
    }
}