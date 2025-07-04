cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

project(Winecraft)

add_executable(Winecraft)

target_include_directories(Winecraft PRIVATE ./include)

file(GLOB_RECURSE CPPS src/*.cpp)
target_sources(Winecraft PRIVATE ${CPPS})

file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)
target_sources(Winecraft PRIVATE ${HEADERS})

include(FetchContent)

# glfw
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Winecraft PRIVATE glfw opengl32)

# glad
target_include_directories(Winecraft PRIVATE dep/glad/include)
target_sources(Winecraft PRIVATE dep/glad/src/glad.c)

# stb
target_include_directories(Winecraft PRIVATE dep/stb/include)
target_sources(Winecraft PRIVATE dep/stb/src/stb_image.cpp)

# glm
find_package(glm CONFIG REQUIRED)
target_link_libraries(Winecraft PRIVATE glm::glm)

# assimp
find_package(assimp CONFIG REQUIRED)
target_link_libraries(Winecraft PRIVATE assimp::assimp)

# arduinoJson
FetchContent_Declare(ArduinoJson
    GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git
    GIT_TAG        v7.3.0
)
FetchContent_MakeAvailable(ArduinoJson)
target_link_libraries(Winecraft PRIVATE ArduinoJson)

# freetype
find_package(Freetype REQUIRED)
target_include_directories(Winecraft PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(Winecraft PRIVATE ${FREETYPE_LIBRARIES})

# boost_signals2
find_package(boost_signals2 REQUIRED CONFIG)
target_link_libraries(Winecraft PRIVATE Boost::signals2)
