#include "Mathf.h"
#include <cstdlib>
#include <ctime>

int Mathf::RandomIntRange(int min, int max)
{
    return min + std::rand() % (max - min);
}

float Mathf::Random01()
{
    return (float) std::rand() / RAND_MAX;
}

float Mathf::RandomFloatRange(float min, float max)
{
    return min + Random01() * (max - min);
}

glm::vec2 Mathf::RandomDir2D()
{
    return glm::normalize(glm::vec2(RandomFloatRange(-1, 1), RandomFloatRange(-1, 1)));
}

void Mathf::init()
{
    std::srand(std::time(0));
}