#include "Game/GameSystem.h"
#include "UI/Image.h"
#include "Render/Texture.h"
#include "Core/Branch.h"
#include "Render/RenderSystem.h"

void GameSystem::Awake()
{
    SingletonNode<GameSystem>::Awake();

    // 准星
    aimerBra = Branch::NewBranch("aimerBra");
    aimer = aimerBra->AddNode<Image>("aimer");
    aimer->SetTex(Resource::Load<Texture>("res/texture/aimer.json"));
    aimer->SetSize({50, 50});
}

void GameSystem::Update()
{
    // 保持中间
    vec2 size = RenderSystem::Instance()->GetWindowSize();
    aimerBra->SetPosition({size.x / 2, size.y / 2, 0});
}