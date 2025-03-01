#include <glad/glad.h>
#include "Common/Skybox.h"
#include "Core/Branch.h"
#include "Render/Material/SkyboxMaterial.h"
#include "Render/Mesh/Mesh1.h"
#include "Render/Renderer.h"

void Skybox::OnAdded()
{
    renderer = GetParent().lock()->GetChildOrAdd<Renderer>();

    auto mat_Skybox =
        Resource::Load<SkyboxMaterial>("res/material/skybox.json");

    renderer->SetMaterial(mat_Skybox);
    renderer->SetMesh(Mesh1::CreateSkyboxCube());
    renderer->SetOrder(INT_MIN); // 天空盒一定要最先渲染
}