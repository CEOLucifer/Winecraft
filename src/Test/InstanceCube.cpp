#include "glad/glad.h"
#include "Test/InstanceCube.h"
#include "Render/Material/InstanceMaterial.h"
#include "Render/Material/RealMaterial.h"
#include "Render/Mesh/Mesh3.h"
#include "Render/Renderer.h"
#include "Resource/Resource.h"

void InstanceCube::Awake()
{
    name = "instanceCube";
    auto renderer = AddNode<Renderer>();
    renderer->SetMesh(Mesh3::LoadCube());
    renderer->SetMaterial(
        Resource::Load<InstanceMaterial>("res/material/instance.json"));

    // renderer->SetMaterial(
    //     Resource::Load<RealMaterial>("res/material/container.json"));
}