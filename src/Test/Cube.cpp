#include "glad/glad.h"
#include "Test/Cube.h"
#include "Render/Material/RealMaterial.h"
#include "Render/Renderer.h"
#include "Render/Mesh/Mesh3.h"

void Cube::Awake()
{
    renderer = AddNode<Renderer>("cubeRenderer");

    auto mat_Container =
        Resource::Load<RealMaterial>("res/material/container.json");
    renderer->SetMaterial(mat_Container);

    renderer->SetMesh(Mesh3::LoadCube());

    // 创建箱子的边框
    // auto border = Node::Create<Border>();
    // border->position = cubePositions[i];
    // border->scale = {1.1, 1.1, 1.1};
    // border->SetMesh(meshCube);
    // border->SetMaterial(mat_Border);
}