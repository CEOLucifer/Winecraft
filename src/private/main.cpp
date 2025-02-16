#include "CameraController.h"
#include "Mesh.h"
#include "Node/NodeSystem.h"
#include "Node/Parentable.h"
#include "Resource/ResourceSystem.h"
#include "Shader.h"
#include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"
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

using namespace std;



void Run()
{
    NodeSystem::LoadInstance();
    RenderSystem::LoadInstance();
    GLFWwindow* window = RenderSystem::Instance()->GetWindow();
    Input::SetWindow(window);
    ResourceSystem::LoadInstance();

    // 创建顶点着色器
    auto vertexShader =
        Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/vert0.vert");
    // 创建片段着色器
    auto fragmentShader =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag0.frag");
    auto fragmentShader_1 =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag1.frag");
    auto fragmentShader_light =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/lightFrag.frag");
    // 创建着色器程序
    auto shaderProgram = ShaderProgram::Create({vertexShader, fragmentShader});
    auto shaderProgram_1 =
        ShaderProgram::Create({vertexShader, fragmentShader_1});
    auto shaderProgram_light =
        ShaderProgram::Create({vertexShader, fragmentShader_light});
    shaderProgram->setInt("texture1", 0);
    shaderProgram->setInt("texture2", 1);
    // shaderProgram_1->SetVec3("material.ambient", {0.2f, 0.2f, 0.2f});
    shaderProgram_1->setInt("material.diffuse", 0);
    shaderProgram_1->setInt("material.specular", 1);
    shaderProgram_1->SetVec3("material.diffuse", {1.0f, 0.5f, 0.31f});
    shaderProgram_1->SetVec3("material.specular", {1.0f, 1.0f, 1.0f});
    shaderProgram_1->setFloat("material.shininess", 32.0f);
    shaderProgram_1->SetVec3("light.ambient", {1, 1, 1});



    // 纹理
    TextureFactory texFac;
    auto tex0 = texFac.Create("res/container.jpg");
    auto tex1 = texFac.Create("res/awesomeface.png");
    auto tex2 = texFac.Create("res/container2.png");
    auto tex3 = texFac.Create("res/container2_specular.png");

    MeshFactory meshFac;
    auto meshCube = meshFac.CreateCube();

    // 模型
    ModelFactory modelFac;
    auto backpackModel = modelFac.Create("res/cylinder.obj");


    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    for (int i = 0; i < cubePositions.size(); ++i)
    {
        auto cube = Node::Create<Cube>();
        // cube->renderer->SetMesh(meshCube);
        cube->renderer->SetMesh(backpackModel->GetMeshes()[0]);
        cube->renderer->position = cubePositions[i];
        cube->renderer->SetShaderProgram(shaderProgram_1);
        cube->renderer->SetTexs({tex2, tex3});
        cube->renderer->scale = {0.02, 0.02, 0.02};
    }

    // auto light = Renderer::Create();
    // light->SetMesh(meshCube);
    // light->SetShaderProgram(shaderProgram_1);
    // auto spotLight = Node::Create<SpotLight>();
    auto spotLightCube = Node::Create<SpotLightCube>();
    spotLightCube->renderer->SetMesh(meshCube);
    spotLightCube->renderer->SetShaderProgram(shaderProgram_light);
    spotLightCube->renderer->position = {10, 0, 0};
    spotLightCube->spotLight->Color = {1, 1, 1};


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

        // 渲染
        RenderSystem::Instance()->Render();

        glfwSwapBuffers(window);
    }

    ResourceSystem::UnloadInstance();
    RenderSystem::UnloadInstance();
    NodeSystem::UnloadInstance();
}

int main()
{
    try
    {
        Run();
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
    return 0;
}