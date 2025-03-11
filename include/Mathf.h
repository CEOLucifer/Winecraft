#pragma once

#include <glm/glm.hpp>

class Mathf
{
    friend class App;

public:
    static int RandomIntRange(int min, int max);

    static float Random01();

    static float RandomFloatRange(float min, float max);

    static glm::vec2 RandomDir2D();

private:
    static void init();
};