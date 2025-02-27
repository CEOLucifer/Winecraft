#include "App.h"
#include <climits>
#include <glad/glad.h>
#include "CameraController.h"
#include "Core/Node.h"
#include "Core/CoreSystem.h"
#include "Core/Branch.h"
#include "Mesh.h"
#include "Render/DirectionalLight.h"
#include "Render/FrameBuffer.h"
#include "Render/Material/Material.h"
#include "Render/Material/SkyboxMaterial.h"
#include "Render/Shader/ControlShaderProgram.h"
#include "Render/Shader/SkyboxShaderProgram.h"
#include "Render/SpotLight.h"
#include "Resource/ResourceSystem.h"
#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Render/Shader/RealShaderProgram.h"
#include "Render/Shader/ShaderProgram.h"
#include "Texture.h"
#include "glm/fwd.hpp"
#include <memory>
#include <stb/stb_image.h>
#include <stdexcept>
#include <string>
#include <vector>
#include "Render/RenderSystem.h"
#include "Camera.h"
#include "InputSystem.h"
#include "Render/Model.h"
#include "Render/Renderer.h"
#include "Render/Material/RealMaterial.h"
#include "Render/Material/SingleColorMaterial.h"
#include "Debug/Debug.h"
#include "TimeSystem.h"
#include "MeshFactory.h"
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
    // 创建顶点着色器
    auto vs = Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/vert0.vert");
    auto vs_skybox =
        Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/skybox.vert");
    auto vs_control =
        Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/control.vert");
    // 创建片段着色器
    auto fs = Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag0.frag");
    auto fs_Universal =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/real.frag");
    auto fs_SingleColor =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/singleColor.frag");
    auto fs_Depth =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/depth.frag");
    auto fs_skybox =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/skybox.frag");
    auto fs_control =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/control.frag");
    // 创建着色器程序
    auto sp = ShaderProgram::Create<RealShaderProgram>({vs, fs});
    auto sp_Universal =
        ShaderProgram::Create<RealShaderProgram>({vs, fs_Universal});
    auto sp_SingleColor =
        ShaderProgram::Create<RealShaderProgram>({vs, fs_SingleColor});
    auto sp_Depth = ShaderProgram::Create<ShaderProgram>({vs, fs_Depth});
    auto sp_skybox =
        ShaderProgram::Create<SkyboxShaderProgram>({vs_skybox, fs_skybox});
    auto sp_control =
        ShaderProgram::Create<ControlShaderProgram>({vs_control, fs_control});


    // 纹理
    TextureFactory texFac;
    auto tex0 = texFac.Create("res/container.jpg");
    auto tex1 = texFac.Create("res/awesomeface.png");
    auto tex_Container = texFac.Create("res/container2.png");
    auto tex_ContainerSpecular = texFac.Create("res/container2_specular.png");
    auto tex_Grass = texFac.Create("res/grass.png");
    auto tex_Window = texFac.Create("res/blending_transparent_window.png");
    auto tex_skybox =
        texFac.CreateCube({"res/skybox/right.jpg", "res/skybox/left.jpg",
                           "res/skybox/top.jpg", "res/skybox/bottom.jpg",
                           "res/skybox/front.jpg", "res/skybox/back.jpg"});

    // 网格
    MeshFactory meshFac;
    auto mesh_Cube = meshFac.CreateCube();
    auto mesh_Plane = meshFac.CreatePlane();
    auto mesh_Skybox = meshFac.CreateMesh1_Skybox();
    auto mesh_Control = meshFac.CreateMesh2_Control();

    // 模型
    ModelFactory modelFac;
    // auto backpackModel = modelFac.Create("res/cylinder.obj");
    // auto backpackModel = modelFac.Create("res/backpack/backpack.obj");

    // 材质
    MaterialFactory matFac;
    auto mat_Container = matFac.CreateRaw<RealMaterial>();
    mat_Container->diffuseTex = tex_Container;
    mat_Container->specularTex = tex_ContainerSpecular;
    mat_Container->shaderProgram = sp_Universal;
    mat_Container->StencilFunc.func = GL_ALWAYS;
    mat_Container->StencilFunc.ref = 1;
    mat_Container->StencilMask = 0xFF;
    mat_Container->EnableDepthTest = true;

    auto mat_LightCube = matFac.CreateRaw<SingleColorMaterial>();
    mat_LightCube->shaderProgram = sp_SingleColor;
    mat_LightCube->Color = {1.0, 0, 0};

    auto mat_Border = matFac.CreateRaw<SingleColorMaterial>();
    mat_Border->shaderProgram = sp_SingleColor;
    mat_Border->Color = {1.0, 1.0, 0};
    mat_Border->StencilFunc.func = GL_NOTEQUAL;
    mat_Border->StencilFunc.ref = 1;
    mat_Border->StencilMask = 0x00;

    auto mat_Grass = matFac.CreateRaw<RealMaterial>();
    mat_Grass->diffuseTex = tex_Grass;
    mat_Grass->shaderProgram = sp_Universal;

    auto mat_Window = matFac.CreateRaw<RealMaterial>();
    mat_Window->diffuseTex = tex_Window;
    mat_Window->shaderProgram = sp_Universal;
    mat_Window->EnableBlend = true;

    auto mat_Skybox = matFac.CreateRaw<SkyboxMaterial>();
    mat_Skybox->cubeTexture = tex_skybox;
    mat_Skybox->shaderProgram = sp_skybox;



    // 创建箱子立方体
    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    for (int i = 0; i < cubePositions.size(); ++i)
    {
        auto cube = Branch::Create<Branch>("cube");
        auto renderer = cube->AddNode<Renderer>("cubeRenderer");
        cube->Position = cubePositions[i];
        renderer->SetMesh(mesh_Cube);
        renderer->SetMaterial(mat_Container);
        // cube->SetPolygonMode(GL_POINT);

        // 创建箱子的边框
        // auto border = Node::Create<Border>();
        // border->position = cubePositions[i];
        // border->scale = {1.1, 1.1, 1.1};
        // border->SetMesh(meshCube);
        // border->SetMaterial(mat_Border);
    }

    // 创建窗户
    auto windowObj = Branch::Create("windowObj");
    auto window1 = windowObj->AddNode<Renderer>("windowRenderer");
    window1->SetParent(windowObj);
    windowObj->Position = {5, 0, 5};
    window1->SetMesh(mesh_Plane);
    window1->SetMaterial(mat_Window);
    window1->SetOrder(1);



    // 光源
    auto spotLightObj = Branch::Create("spotLight");
    spotLightObj->Position = {10, 0, 0};
    auto spotLight = spotLightObj->AddNode<SpotLight>();
    spotLight->SetParent(spotLightObj);
    spotLight->Color = {1, 0, 0};

    auto spotLightRenderer = spotLightObj->AddNode<Renderer>();
    spotLightRenderer->SetParent(spotLightObj);
    spotLightRenderer->SetMesh(mesh_Cube);
    spotLightRenderer->SetMaterial(mat_LightCube);


    auto directionalLightObj = Branch::Create("directionalLight");
    auto directionalLight = directionalLightObj->AddNode<DirectionalLight>();
    directionalLight->SetParent(directionalLightObj);





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
    // auto skyboxObj = Node::Create<Branch>("skybox");
    // auto skybox = Node::Create<Renderer>();
    // skybox->SetMaterial(mat_Skybox);
    // skybox->SetMesh(mesh_Skybox);
    // skybox->SetOrder(INT_MIN); // 天空盒一定要最先渲染


    // Image
    auto imageObj = Branch::Create("image");
    auto image = imageObj->AddNode<Image>();
}