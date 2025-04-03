#include "Common/FPSWatcher.h"
#include "Debug/Debug.h"
#include "TimeSystem.h"
#include "UI/Label.h"
#include "Block/BlockSystem.h"
#include "Block/LatticeRenderCenter.h"

void FPSWatcher::OnAdded()
{
    lab = GetParent().lock()->GetChildOrAdd<Label>();
    lab->SetText("FPS: 0");
    lab->SetColor(Color::Red);
}

void FPSWatcher::Update()
{
    freshTimer += Time::GetDeltaTime();
    frameCount += 1;
    if (freshTimer >= freshInterval)
    {
        String str;
        str += std::format("FPS: {}; ", frameCount / (Time::GetRunTime() - lastRunTime));

        // 坐标
        Sp<LatticeRenderCenter> lrc = BlockSystem::Instance()->GetLatticeRenderCenter();
        if(lrc)
        {
            vec3 cor = lrc->GetParent().lock()->Position;
            str += std::format("cor: ({}, {}, {}); ", cor.x, cor.y, cor.z);
        }

        lab->SetText(str);
        freshTimer -= freshInterval;
        frameCount = 0;
        lastRunTime = Time::GetRunTime();
    }
}