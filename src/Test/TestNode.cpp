#include "Test/TestNode.h"
#include "Block/BlockSystem.h"
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
    i32 x = -3;
    Debug::Log(x);


    Map<i32vec2, i32> m;
    m.insert({{0, 0}, 1});
    if (m.contains({0, 0}))
    {
        Debug::Log("yes");
        Debug::Log(m[{0, 0}]);
    }
    else
    {
        Debug::Log("no");
    }
}

void TestNode::Update()
{
    if (Input::GetKey(GLFW_KEY_C, GLFW_PRESS))
    {
        static bool yes = false;

        if(!yes)
        {
            yes = true;
    
            BlockSystem::Instance()->PrintAllSwc();
        }
    }
}