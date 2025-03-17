#include "Common/FPSWatcher.h"
#include "Debug/Debug.h"
#include "TimeSystem.h"

void FPSWatcher::Update()
{
    Debug::Log(1 / Time::GetDeltaTime());
}