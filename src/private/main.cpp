#include "CameraController.h"
#include "Mesh.h"
#include "Node/NodeSystem.h"
#include "Node/Parentable.h"
#include "Shader.h"
#include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"
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

using namespace std;



void Run()
{
    NodeSystem::LoadInstance();
    RenderSystem::LoadInstance();
    GLFWwindow* window = RenderSystem::Instance()->GetWindow();
    Input::SetWindow(window);

    // 创建顶点着色器
    auto vertexShader =
        Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/vert0.vert");
    // 创建片段着色器
    auto fragmentShader =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag0.frag");
    auto fragmentShader_1 =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag1.frag");
    // 创建着色器程序
    auto shaderProgram = ShaderProgram::Create({vertexShader, fragmentShader});
    auto shaderProgram_1 =
        ShaderProgram::Create({vertexShader, fragmentShader_1});
    shaderProgram->setInt("texture1", 0);
    shaderProgram->setInt("texture2", 1);
    shaderProgram_1->SetVec3("objectColor", {1.0f, 0.5f, 0.31f});
    shaderProgram_1->SetVec3("lightColor", {1.0f, 1.0f, 1.0f});
    shaderProgram_1->SetVec3("lightPos", {5, 5, 0});



    // 纹理
    auto tex0 = Texture::Create("res/container.jpg", GL_RGB);
    auto tex1 = Texture::Create("res/awesomeface.png", GL_RGBA);

    auto meshCube = Mesh::CreateCube();

    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    for (int i = 0; i < cubePositions.size(); ++i)
    {
        auto cube = Node::Create<Cube>();
        cube->renderer->SetMesh(meshCube);
        cube->renderer->position = cubePositions[i];
        // cube->renderer->SetTexs({tex0});
        cube->renderer->SetShaderProgram(shaderProgram_1);
    }

    // auto light = Renderer::Create();
    // light->SetMesh(meshCube);
    // light->SetShaderProgram(shaderProgram_1);




    auto camera = Node::Create<Camera>();
    camera->position = {0, 0, 10};
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
        shaderProgram_1->SetVec3("viewPos", camera->position);

        RenderSystem::Instance()->Render();

        glfwSwapBuffers(window);
    }

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