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
        src/Resource/ResourceSystem.cpp
        src/Render/Camera.cpp
        src/Render/DirectionalLight.cpp
        src/Render/FrameBuffer.cpp
        src/Render/Model.cpp
        src/Render/RenderBuffer.cpp
        src/Render/RenderPass.cpp
        src/Render/RenderSystem.cpp
        src/Render/SpotLight.cpp
        src/Render/Texture.cpp
        src/Render/Mesh/Mesh.cpp
        src/Render/Mesh/Mesh1.cpp
        src/Render/Mesh/Mesh2.cpp
        src/Render/Mesh/Mesh3.cpp
        src/Render/Mesh/Mesh_2D_Point.cpp
        src/Core/Branch.cpp
        src/Core/CoreSystem.cpp
        src/Core/Node.cpp
        src/Core/Transform.cpp
        src/Block/Section.cpp
        src/Render/Shader.cpp
        src/Render/ShaderProgram.cpp
        include/Block/BlockRenderPass.h
        src/Block/BlockRenderPass.cpp
        include/Test/CameraController.h
        include/Test/FPSWatcher.h
        src/Test/FPSWatcher.cpp
        include/Block/BlockSystem.h
        src/Block/BlockSystem.cpp
        include/Test/BerlinTest.h
        include/Mathf.h
        src/Mathf.cpp
        include/Creature/Creature.h
        include/Creature/Player.h
        include/UI/Control.h
        src/UI/Control.cpp
        include/UI/Image.h
        include/UI/Label.h
        include/UI/Button.h
        include/UI/Canvas.h
        include/UI/UIRenderPass.h
        src/UI/Canvas.cpp
        src/UI/UIRenderPass.cpp
        include/UI/MeshControl.h
        src/UI/MeshControl.cpp
        src/UI/Image.cpp)

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
FetchContent_Declare(ArduinoJson
    GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git
    GIT_TAG        v7.3.0
)
FetchContent_MakeAvailable(ArduinoJson)
target_link_libraries(LearnOpenGL PRIVATE ArduinoJson)

# freetype
#FetchContent_Declare(freetype
#        GIT_REPOSITORY https://github.com/freetype/freetype
#)
#FetchContent_MakeAvailable(freetype)
#target_link_libraries(LearnOpenGL PRIVATE freetype)

## tgui
## Set properties that will be used while building TGUI
#set(BUILD_SHARED_LIBS OFF)      # Determines whether TGUI build a static or dynamic/shared library
#set(TGUI_BACKEND GLFW_OPENGL3)  # Sets which backend TGUI will use
#FetchContent_Declare(
#        TGUI
#        GIT_REPOSITORY https://github.com/texus/TGUI
#        GIT_TAG v1.4.0  # Change this to wanted version
#)
#FetchContent_MakeAvailable(TGUI)
#target_link_libraries(LearnOpenGL PRIVATE TGUI::TGUI)