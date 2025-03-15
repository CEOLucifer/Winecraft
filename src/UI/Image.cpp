#include "UI/Image.h"
#include "UI/UIRenderPass.h"
#include "Core/Branch.h"
#include "TimeSystem.h"


void Image::Awake()
{
    UIRenderPass::Instance()->imageVec.push_back(CastTo<Image>());
}