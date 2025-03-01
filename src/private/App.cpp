#include "App.h"
#include <climits>
#include <glad/glad.h>
#include "Common/Skybox.h"
#include "Test/CameraController.h"
#include "Core/Node.h"
#include "Core/CoreSystem.h"
#include "Core/Branch.h"
#include "Render/Mesh/Mesh.h"
#include "Render/DirectionalLight.h"
#include "Render/Material/Material.h"
#include "Render/Material/SkyboxMaterial.h"
#include "Render/SpotLight.h"
#include "Resource/ResourceSystem.h"
#include <GLFW/glfw3.h>
#include "Render/Shader/RealShaderProgram.h"
#include "Render/Shader/ShaderProgram.h"
#include "Test/Cube.h"
#include "glm/fwd.hpp"
#include <memory>
#include <stb/stb_image.h>
#include <string>
#include <vector>
#include "Render/RenderSystem.h"
#include "Render/Camera.h"
#include "InputSystem.h"
#include "Render/Renderer.h"
#include "Render/Material/RealMaterial.h"
#include "Render/Material/SingleColorMaterial.h"
#include "TimeSystem.h"
#include "Render/Mesh/MeshFactory.h"
#include "UI/Image.h"

using namespace std;

void App::Run()
{
    CoreSystem::LoadInstance();
    RenderSystem::LoadInstance();
    GLFWwindow* window = RenderSystem::Instance()->GetWindow();
    ResourceSystem::LoadInstance();
    Input::init(window);
    Time::init();

    StartUser();

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        Time::record();
        Input::record();

        CoreSystem::Instance()->UpdateAll();

        // 检查并调用事件
        glfwPollEvents();

        // 渲染
        RenderSystem::Instance()->Render();
    }

    ResourceSystem::UnloadInstance();
    RenderSystem::UnloadInstance();
    CoreSystem::UnloadInstance();
}

void App::StartUser()
{
    // 网格

    // 模型
    // auto backpackModel = modelFac.Create("res/cylinder.obj");
    // auto backpackModel = modelFac.Create("res/backpack/backpack.obj");

    // 材质


    auto mat_LightCube =
        Resource::Load<SingleColorMaterial>("res/material/lightCube.json");

    // auto mat_Border = Resource::Load<SingleColorMaterial>();
    // mat_Border->shaderProgram = sp_SingleColor;
    // mat_Border->Color = {1.0, 1.0, 0};
    // mat_Border->StencilFunc.func = GL_NOTEQUAL;
    // mat_Border->StencilFunc.ref = 1;
    // mat_Border->StencilMask = 0x00;

    auto mat_Grass = Resource::Load<RealMaterial>("res/material/grass.json");

    // auto mat_Window = Resource::Load<RealMaterial>("res/material/container.json");
    // mat_Window->diffuseTex = tex_Window;
    // mat_Window->shaderProgram = sp_Universal;
    // mat_Window->EnableBlend = true;



    // 创建箱子立方体
    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    for (int i = 0; i < cubePositions.size(); ++i)
    {
        auto cube = Branch::Create<Cube>("cube");
        cube->Position = cubePositions[i];

        // 创建箱子的边框
        // auto border = Node::Create<Border>();
        // border->position = cubePositions[i];
        // border->scale = {1.1, 1.1, 1.1};
        // border->SetMesh(meshCube);
        // border->SetMaterial(mat_Border);
    }

    // 创建窗户
    // auto windowObj = Branch::Create("windowObj");
    // auto window1 = windowObj->AddNode<Renderer>("windowRenderer");
    // window1->SetParent(windowObj);
    // windowObj->Position = {5, 0, 5};
    // window1->SetMesh(mesh_Plane);
    // window1->SetMaterial(mat_Window);
    // window1->SetOrder(1);



    // 光源

    // 点光源
    auto spotLightObj = Branch::Create("spotLight");
    spotLightObj->Position = {10, 0, 0};
    auto spotLight = spotLightObj->AddNode<SpotLight>();
    spotLight->SetParent(spotLightObj);
    spotLight->Color = {1, 0, 0};

    auto spotLightRenderer = spotLightObj->AddNode<Renderer>();
    spotLightRenderer->SetParent(spotLightObj);
    spotLightRenderer->SetMesh(Mesh3::LoadCube());
    spotLightRenderer->SetMaterial(mat_LightCube);

    // 定向光
    auto directionalLightObj = Branch::Create("directionalLight");
    auto directionalLight = directionalLightObj->AddNode<DirectionalLight>();
    directionalLight->SetParent(directionalLightObj);
    directionalLight->intensity = 0.05;





    // 摄像机
    auto cameraObj = Branch::Create("camera");
    auto camera = cameraObj->AddNode<Camera>();
    camera->SetParent(cameraObj);
    cameraObj->Position = {5, 0, 10};
    auto cameraController = cameraObj->AddNode<CameraController>();
    cameraController->SetParent(cameraObj);
    cameraController->camera = camera;



    // 帧缓冲
    // auto frameBuffer = FrameBuffer::CreateUtility(800, 600);

    // 输出到自定义帧缓冲的摄像机
    // auto camera_FrameBuffer = Node::Create<Camera>();
    // camera_FrameBuffer->position = {10, 0, 10};
    // camera_FrameBuffer->rotation.y = 45;
    // camera_FrameBuffer->SetTargetFrameBuffer(frameBuffer);

    // auto mat_FrameBuffer = matFac.CreateRaw<RealMaterial>();
    // mat_FrameBuffer->shaderProgram = sp_Universal;
    // mat_FrameBuffer->diffuseTex = frameBuffer->GetTexture();

    // auto cube = Node::Create<Renderer>();
    // cube->position = {5, 0, 0};
    // cube->SetMesh(mesh_Cube);
    // cube->SetMaterial(mat_FrameBuffer);

    // 天空盒
    auto skyboxObj = Branch::Create("skybox");
    auto skybox = skyboxObj->AddNode<Skybox>();



    // Image
    // auto imageObj = Branch::Create("image");
    // auto image = imageObj->AddNode<Image>();
    // imageObj->Scale = {1000, 1000, 1};
}