#include <glad/glad.h>
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
}