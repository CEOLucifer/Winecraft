cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 23)

project(LearnOpenGL)

add_executable(LearnOpenGL)

file(GLOB_RECURSE Cpps src/private/*.cpp)
target_sources(LearnOpenGL PRIVATE ${Cpps})

target_include_directories(LearnOpenGL PRIVATE src/public)

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