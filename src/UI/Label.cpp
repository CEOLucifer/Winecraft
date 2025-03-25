#include "UI/Label.h"
#include "UI/UIRenderPass.h"

void Label::Awake()
{
    Control::Awake();
    font = Resource::Load<Font>("res/font/arial.json");

    UIRenderPass::Instance()->labelVec.push_back(CastTo<Label>());
}
