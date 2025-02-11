#include "Renderer.h"
#include "Shader.h"
#include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "ShaderProgram.h"
#include "Texture.h"
#include "Vertex.h"
#include "glm/fwd.hpp"
#include <stb/stb_image.h>
#include <string>
#include <vector>

using namespace std;

void onFrameBufferResize(GLFWwindow* window, int w, int h)
{
    glViewport(0, 0, w, h);
}

void Run()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, 800, 600);
    // 启用深度检测。此时交换链有深度字段。
    glEnable(GL_DEPTH_TEST);

    // 事件监听
    glfwSetFramebufferSizeCallback(window, onFrameBufferResize);

    // 查询顶点着色器的顶点属性上限
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
              << std::endl;

    // 创建顶点着色器
    auto vertexShader =
        Shader::CreateFromFile(GL_VERTEX_SHADER, "shader/vert1.vert");
    // 创建片段着色器
    auto fragmentShader =
        Shader::CreateFromFile(GL_FRAGMENT_SHADER, "shader/frag1.frag");
    // 创建着色器程序
    auto shaderProgram = ShaderProgram::Create({vertexShader, fragmentShader});
    shaderProgram->setInt("texture1", 0);
    shaderProgram->setInt("texture2", 1);



    // 纹理
    auto tex0 = Texture::Create("res/container.jpg", GL_RGB);
    auto tex1 = Texture::Create("res/awesomeface.png", GL_RGBA);


    vector<Vertex> vertices = {
        //     ---- 位置 ----       ---- 法线 ----     - 纹理坐标 -
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},   // 右上
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},  // 右下
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 左下
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},  // 左上
    };

    vector<uint32_t> indices = {
        0, 1, 3, //
        1, 2, 3, //
    };

    // vector<float> vertices1 = {
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    //     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //     -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

    //     -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    //     0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    //     -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
    //     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //     -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    auto mesh = Mesh::Create();
    mesh->SetVertices(std::move(vertices));
    mesh->SetIndices(std::move(indices));


    vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    vector<shared_ptr<Renderer>> objs;
    for (int i = 0; i < cubePositions.size(); ++i)
    {
        auto obj = Renderer::Create();
        obj->SetMesh(mesh);
        obj->position = cubePositions[i];
        obj->SetTexs({ tex0});
        obj->SetShaderProgram(shaderProgram);
        objs.push_back(obj);
    }

    Camera camera;
    camera.position = {0, 0, 10};
    float cameraSpeed = 3;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 输入
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glm::vec3 posDelta = {};
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            posDelta = cameraSpeed * camera.GetForward();
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            posDelta = -cameraSpeed * camera.GetForward();
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            posDelta = -camera.GetRight() * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            posDelta = camera.GetRight() * cameraSpeed;
        posDelta *= deltaTime;

        // cout << format("{} {} {}", posDelta.x, posDelta.y, posDelta.z) <<
        // endl;

        camera.position += posDelta;

        objs[0]->position.z -= 0.5 * deltaTime;

        // 检查并调用事件
        glfwPollEvents();


        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // obj1->Draw(camera);
        for (auto each : objs)
        {
            each->rotation = {glfwGetTime() * 10, glfwGetTime() * 5, 0};
            each->Draw(camera);
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
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