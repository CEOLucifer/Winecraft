#include "UI/Image.h"
#include "UI/UIRenderPass.h"
#include "Core/Branch.h"
#include "TimeSystem.h"


void Image::Awake()
{
    UIRenderPass::Instance()->imageVec.push_back(CastTo<Image>());
}

void Image::Update()
{
    GetParent().lock()->Position.y += 50 * Time::GetDeltaTime();
//    Debug::Log(GetParent().lock()->Position);
}