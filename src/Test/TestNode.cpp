#include "Test/TestNode.h"
#include "InputSystem.h"
#include "Render/RenderSystem.h"
#include "Render/Camera.h"

void TestNode::Update()
{
    if (Input::GetKey(GLFW_KEY_P, GLFW_PRESS))
    {
        auto camera = RenderSystem::Instance()->GetFirstCamera();
        camera->GetParent().lock()->Position = {53, 80, 53};
    }

    if (Input::GetKey(GLFW_KEY_O, GLFW_PRESS))
    {
        auto camera = RenderSystem::Instance()->GetFirstCamera();
        camera->GetParent().lock()->Position;


    }
}