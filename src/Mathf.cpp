#include "Mathf.h"
#include "Block/Section.h"
#include <cstdlib>
#include <ctime>

int Mathf::seed = 0;

int Mathf::RandomIntRange(int min, int max)
{
    return min + std::rand() % (max - min + 1);
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
    seed = std::rand();
}

int Mathf::Hash21(glm::i32vec2 x)
{
    // 定义一些用于哈希计算的常数
    int prime1 = seed + 31; // 一个较小的质数，常用于哈希计算
    int prime2 = seed + 127; // 另一个质数，用于增加哈希的分散性

    // 初始化哈希值，可以使用坐标的一个分量或者一个固定的初始值
    int hash = x.x;

    // 将x坐标的影响加入到哈希值中
    hash = hash * prime1 + x.y;

    // 可选：为了进一步混合坐标的影响，可以添加一些位运算
    // 例如，右移和异或运算
    hash = (hash >> 16) ^ (hash & 0xFFFF);
    hash *= prime2;

    // 如果需要，可以添加更多的混合步骤
    // ...

    // 返回最终的哈希值
    // 注意：如果需要限制哈希值的范围，可以使用模运算（例如 hash % some_value）
    // 但在这个例子中，我们直接返回计算得到的哈希值
    return hash;
}

uint32_t Mathf::GetHeight(glm::i32vec2 coords)
{
    return 1 + abs(Hash21(coords)) % Section::Height;
}
