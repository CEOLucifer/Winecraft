#include "App.h"
#include "CameraController.h"
#include "Mesh.h"
#include "Node/NodeSystem.h"
#include "Node/Parentable.h"
#include "Render/Material.h"
#include "Render/Shader/DepthSP.h"
#include "Resource/ResourceSystem.h"
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render/Shader/UniversalShaderProgram.h"
#include "SpotLightCube.h"
#include "Texture.h"
#include "glm/fwd.hpp"
#include <memory>
#include <stb/stb_image.h>
#include <string>
#include <vector>
#include "Render/RenderSystem.h"
#include "Cube.h"
#include "Camera.h"
#include "InputSystem.h"
#include "Render/Model.h"
#include "Render/Renderer.h"

using namespace std;

void App::Run()
{
    NodeSystem::LoadInstance();
    RenderSystem::LoadInstance();
    GLFWwindow* window = RenderSystem::Instance()->GetWindow();
    Input::SetWindow(window);
    ResourceSystem::LoadInstance();

    // 创建顶点着色器
    auto vs = Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/vert0.vert");
    // 创建片段着色器
    auto fs = Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag0.frag");
    auto fs_Universal =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/universal.frag");
    auto fs_SingleColor =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/singleColor.frag");
    auto fs_Depth =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/depth.frag");
    // 创建着色器程序
    auto sp = ShaderProgram::Create<UniversalShaderProgram>({vs, fs});
    auto sp_Universal =
        ShaderProgram::Create<UniversalShaderProgram>({vs, fs_Universal});
    auto sp_SingleColor =
        ShaderProgram::Create<UniversalShaderProgram>({vs, fs_SingleColor});
    auto sp_Depth = ShaderProgram::Create<DepthSP>({vs, fs_Depth});


    // 纹理
    TextureFactory texFac;
    auto tex0 = texFac.Create("res/container.jpg");
    auto tex1 = texFac.Create("res/awesomeface.png");
    auto tex_Container = texFac.Create("res/container2.png");
    auto tex_ContainerSpecular = texFac.Create("res/container2_specular.png");
    // auto tex4 = texFac.Create("res/backpack/diffuse.jpg");
    // auto tex5 = texFac.Create("res/backpack/specular.jpg");

    MeshFactory meshFac;
    auto meshCube = meshFac.CreateCube();

    // 模型
    ModelFactory modelFac;
    // auto backpackModel = modelFac.Create("res/cylinder.obj");
    // auto backpackModel = modelFac.Create("res/backpack/backpack.obj");

    // 材质
    MaterialFactory matFac;
    auto mat = matFac.CreateRaw();
    mat->diffuseTex = tex_Container;
    mat->specularTex = tex_ContainerSpecular;
    mat->shaderProgram = sp_Universal;

    auto mat_LightCube = matFac.CreateRaw();
    mat_LightCube->shaderProgram = sp_SingleColor;

    auto mat_SingleColor = matFac.CreateRaw();
    mat_SingleColor->shaderProgram = sp_SingleColor;



    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    // 生成箱子立方体
    for (int i = 0; i < cubePositions.size(); ++i)
    {
        auto cube = Node::Create<Cube>();
        cube->renderer->SetMesh(meshCube);
        // cube->renderer->SetMesh(backpackModel->GetMeshes()[0]);
        cube->renderer->SetMaterial(mat);
        cube->renderer->position = cubePositions[i];
        // cube->renderer->scale = {0.02, 0.02, 0.02};
    }

    // 光源
    auto spotLightCube = Node::Create<SpotLightCube>();
    spotLightCube->renderer->SetMesh(meshCube);
    spotLightCube->renderer->SetMaterial(mat_LightCube);
    spotLightCube->renderer->position = {10, 0, 0};
    spotLightCube->spotLight->Color = {1, 1, 1};

    auto directionalLight = Node::Create<DirectionalLight>();

    // 摄像机
    auto camera = Node::Create<Camera>();
    camera->position = {5, 0, 10};
    auto cameraController = Node::Create<CameraController>();
    cameraController->camera = camera;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        NodeSystem::Instance()->Update(deltaTime);

        // 检查并调用事件
        glfwPollEvents();
        Input::SetLastCursorPos(Input::GetCursorPos());

        // 渲染
        RenderSystem::Instance()->Render();
    }

    ResourceSystem::UnloadInstance();
    RenderSystem::UnloadInstance();
    NodeSystem::UnloadInstance();
}
