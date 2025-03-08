#pragma once

#include <chrono>

class Time
{
    friend class App;

private:
    static std::chrono::system_clock::time_point initStack;
    static std::chrono::system_clock::time_point lastStack;
    static float deltaTime;
    static float runTime;

public:
    static float GetDeltaTime() { return deltaTime; }

    static float GetRunTime() { return runTime; }

private:
    static void init()
    {
        initStack = lastStack = std::chrono::system_clock::now();
    }

    static void record()
    {
        auto curStack = std::chrono::system_clock::now();
        std::chrono::duration<float> x = curStack - lastStack;
        deltaTime = x.count();
        lastStack = curStack;

        std::chrono::duration<float> y = lastStack - initStack;
        runTime = y.count();
    }
};