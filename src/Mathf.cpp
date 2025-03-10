#include "Mathf.h"
#include <cstdlib>

int Mathf::RandomIntRange(int min, int max)
{
    return min + std::rand() % (max - min);
}