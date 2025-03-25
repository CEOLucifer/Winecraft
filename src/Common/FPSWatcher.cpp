#include "Common/FPSWatcher.h"
#include "Debug/Debug.h"
#include "TimeSystem.h"
#include "UI/Label.h"

void FPSWatcher::OnAdded()
{
    lab = GetParent().lock()->GetChildOrAdd<Label>();
    lab->SetText("FPS: 0");
}

void FPSWatcher::Update()
{
    freshTimer += Time::GetDeltaTime();
    frameCount += 1;
    if (freshTimer >= freshInterval)
    {
        lab->SetText(std::format("FPS: {}", frameCount / (Time::GetRunTime() - lastRunTime)));
        freshTimer -= freshInterval;
        frameCount = 0;
        lastRunTime = Time::GetRunTime();
    }
}