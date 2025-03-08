cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 23)

project(LearnOpenGL)

add_executable(LearnOpenGL
        src/App.cpp
        src/CameraController.cpp
        src/FileHelper.cpp
        src/InputSystem.cpp
        src/main.cpp
        src/TimeSystem.cpp
        src/UI/Image.cpp
        src/Test/Cube.cpp
        src/Test/InstanceCube.cpp
        src/Resource/ResourceSystem.cpp
        src/Render/Camera.cpp
        src/Render/DirectionalLight.cpp
        src/Render/FrameBuffer.cpp
        src/Render/Model.cpp
        src/Render/RenderBuffer.cpp
        src/Render/Renderer.cpp
        src/Render/RenderPass.cpp
        src/Render/RenderSystem.cpp
        src/Render/SpotLight.cpp
        src/Render/Texture.cpp
        src/Render/Mesh/Mesh.cpp
        src/Render/Mesh/Mesh1.cpp
        src/Render/Mesh/Mesh2.cpp
        src/Render/Mesh/Mesh3.cpp
        src/Render/Mesh/Mesh_2D_Point.cpp
        src/Render/Material/ControlMaterial.cpp
        src/Render/Material/InstanceMaterial.cpp
        src/Render/Material/Material.cpp
        src/Render/Material/RealMaterial.cpp
        src/Render/Material/SingleColorMaterial.cpp
        src/Render/Material/SkyboxMaterial.cpp
        src/Core/Branch.cpp
        src/Core/CoreSystem.cpp
        src/Core/Node.cpp
        src/Core/Transform.cpp
        src/Common/Skybox.cpp
        src/Block/Section.cpp
        src/Render/Shader/ControlShaderProgram.cpp
        src/Render/Shader/RealShaderProgram.cpp
        src/Render/Shader/Shader.cpp
        src/Render/Shader/ShaderProgram.cpp
        src/Render/Shader/SkyboxShaderProgram.cpp)

target_include_directories(LearnOpenGL PRIVATE ./include)

include(FetchContent)

# glfw
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_MakeAvailable(glfw)
target_link_libraries(LearnOpenGL PRIVATE glfw)

# glad
target_include_directories(LearnOpenGL PRIVATE dep/glad/include)
target_sources(LearnOpenGL PRIVATE dep/glad/src/glad.c)

# stb
target_include_directories(LearnOpenGL PRIVATE dep/stb/include)
target_sources(LearnOpenGL PRIVATE dep/stb/src/stb_image.cpp)

# glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
)
FetchContent_MakeAvailable(glm)
target_link_libraries(LearnOpenGL PRIVATE glm)

# assimp
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp
)
FetchContent_MakeAvailable(assimp)
target_link_libraries(LearnOpenGL PRIVATE assimp)

# arduinoJson
include(FetchContent)
FetchContent_Declare(ArduinoJson
    GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git
    GIT_TAG        v7.3.0
)
FetchContent_MakeAvailable(ArduinoJson)
target_link_libraries(LearnOpenGL PRIVATE ArduinoJson)