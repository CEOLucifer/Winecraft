#include "UI/Canvas.h"
#include "UI/UIRenderPass.h"

void Canvas::Awake()
{
    auto renderPass = Object::NewObject<UIRenderPass>();
    renderPass->canvas = CastTo<Canvas>();
}