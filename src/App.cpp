#include "glad/glad.h"
#include "App.h"
#include "Common/Skybox.h"
#include "Core/Branch.h"
#include "Render/DirectionalLight.h"
#include "Render/SpotLight.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"
#include "Render/RenderSystem.h"
#include "Render/Camera.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "Block/Section.h"
#include "Common/CameraController.h"
#include "Block/BlockRenderPass.h"
#include "Common/FPSWatcher.h"
#include "Block/BlockSystem.h"
#include "Mathf.h"
#include "UI/Image.h"
#include "Resource/Resource.h"
#include "Render/Texture.h"
#include "UI/UIRenderPass.h"
#include "UI/Button.h"
#include "Block/LatticeRenderCenter.h"
#include "UI/Label.h"
#include "Test/TestNode.h"
#include "Common/SkyboxRenderPass.h"
#include "Creature/Player.h"
#include "Common/Rigidbody.h"
#include "Game/GameSystem.h"

using namespace std;

void App::Run()
{
    CoreSystem::LoadInstance();
    RenderSystem::LoadInstance();
    GLFWwindow* window = RenderSystem::Instance()->GetWindow();
    ResourceSystem::LoadInstance();
    BlockSystem::LoadInstance();
    Input::init(window);
    Time::init();
    Mathf::init();

    StartUser();

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        Time::record();
        Input::record();

        CoreSystem::Instance()->UpdateAll();

        Input::ResetMouseActions();
        BlockSystem::Instance()->Update();

        // 检查并调用事件
        glfwPollEvents();


        // 渲染
        RenderSystem::Instance()->Render();
    }

    BlockSystem::UnloadInstance();
    ResourceSystem::UnloadInstance();
    RenderSystem::UnloadInstance();
    CoreSystem::UnloadInstance();
}

void App::StartUser()
{
    Object::NewObject<UIRenderPass>();
    Node::NewNode<GameSystem>("gameSystem");


    // 玩家
    Sp<Player> player = Branch::NewBranch<Player>("player");
    player->SetPosition({0, 150, 0});

//    auto lrcBra = Branch::NewBranch("lrcBra");
//    lrcBra->AddNode<LatticeRenderCenter>();


    // 按钮
//    auto btnBra = Branch::NewBranch("btnBra");
//    auto btn = btnBra->AddNode<Button>();
//    btnBra->Position = {300, 300 , 0};
//    btn->SetSize({100, 60});
//
//    btn->OnDown([]()
//                {
//                    Debug::Log("onDown");
//                });
//
//    btn->OnUp([]()
//              {
//                  Debug::Log("onUp");
//              });
//
//    auto img = btnBra->AddNode<Image>();
//    img->SetTex(Resource::Load<Texture>("res/texture/btn.json"));


    // 标签
    auto labBra = Branch::NewBranch("labBra");
    auto lab = labBra->AddNode<Label>();
    lab->SetColor(Color::Yellow);
    labBra->AddNode<FPSWatcher>();
    labBra->Position.y = 10;

    Branch::NewBranch<TestNode>("TestNode");



//    auto imgBra = Branch::Create("ImageBra");
//    auto img = imgBra->AddNode<Image>();
//    img->SetTex(Resource::Load<Texture>("res/texture/container.json"));
//    img->SetSize({100, 100});

    //    auto mat_LightCube =
    //            Resource::Load<SingleColorMaterial>("res/material/lightCube.json");

    // auto mat_Border = Resource::Load<SingleColorMaterial>();
    // mat_Border->shaderProgram = sp_SingleColor;
    // mat_Border->Color = {1.0, 1.0, 0};
    // mat_Border->StencilFunc.func = GL_NOTEQUAL;
    // mat_Border->StencilFunc.ref = 1;
    // mat_Border->StencilMask = 0x00;

    //    auto mat_Grass =
    //    Resource::Load<RealMaterial>("res/material/grass.json");

    // auto mat_Window =
    // Resource::Load<RealMaterial>("res/material/container.json");
    // mat_Window->diffuseTex = tex_Window;
    // mat_Window->shaderProgram = sp_Universal;
    // mat_Window->EnableBlend = true;



    // 创建箱子立方体
    // vector<glm::vec3> cubePositions = {
    //     glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    //     glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    //     glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    //     glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    //     glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    // for (int i = 0; i < cubePositions.size(); ++i)
    // {
    //     auto cube = Branch::Create<Cube>("cube");
    //     cube->Position = cubePositions[i];
    // }

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
    //    auto spotLightObj = Branch::Create("spotLight");
    //    spotLightObj->Position = {10, 0, 0};
    //    auto spotLight = spotLightObj->AddNode<SpotLight>();
    //    spotLight->SetParent(spotLightObj);
    //    spotLight->Color = {1, 0, 0};
    //
    //    auto spotLightRenderer = spotLightObj->AddNode<Renderer>();
    //    spotLightRenderer->SetParent(spotLightObj);
    //    spotLightRenderer->SetMesh(Mesh3::LoadCube());
    //    spotLightRenderer->SetMaterial(mat_LightCube);

    // 定向光
    //    auto directionalLightObj = Branch::Create("directionalLight");
    //    auto directionalLight =
    //    directionalLightObj->AddNode<DirectionalLight>();
    //    directionalLight->SetParent(directionalLightObj);
    //    directionalLight->intensity = 0.05;









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
    SkyboxRenderPass::LoadInstance();
    SkyboxRenderPass::Instance()->SetRenderOrder(-1000);
    auto skyboxObj = Node::NewNode<Skybox>("skybox");


    // Image
    // auto imageObj = Branch::Create("image");
    // auto image = imageObj->AddNode<Image>();
    // imageObj->Scale = {1000, 1000, 1};




    // 几何着色器测试
    // auto geoMesh = Mesh_2D_Point::CreateRaw();
    // geoMesh->SetVertices({
    //     -0.5f, 0.5f, // 左上
    //     0.5f, 0.5f,  // 右上
    //     0.5f, -0.5f, // 右下
    //     -0.5f, -0.5f // 左下
    // });

    // auto geoBra = Branch::Create("geoBra");
    // auto geoRenderer = geoBra->AddNode<Renderer>();
    // geoRenderer->SetMesh(geoMesh);
    // geoRenderer->SetPrimitiveMode(GL_POINTS);
    // geoRenderer->SetMaterial(Resource::Load<Material>("res/material/geo.json"));
    // // auto geoMat = geoRenderer->GetMaterial();
    // geoRenderer->SetPolygonMode(GL_LINE);


    // 实例化测试
    //    auto instanceCube = Branch::Create<InstanceCube>();
}