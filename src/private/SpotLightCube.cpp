#include "SpotLightCube.h"
#include "Core/Component.h"
#include "Render/Renderer.h"
#include "Render/SpotLight.h"
#include "Render/Shader/ShaderProgram.h"
#include "Render/Material/Material.h"
#include <memory>
#include "Core/GameObject.h"

using namespace std;

void SpotLightCube::Awake()
{
    auto gameObject = GetGameObject();
    gameObject->Position = {10, 0, 0};

    spotLight = Component::Create<SpotLight>();
    gameObject->AddComponent(spotLight);

    renderer = Component::Create<Renderer>();
    gameObject->AddComponent(renderer);
}

void SpotLightCube::Update() {}