#include "Mathf.h"
#include "Block/Section.h"
#include "Debug/Debug.h"
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
//    seed = std::rand();
    seed = 28490;
    Debug::Log(seed);
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

glm::i32vec2 Mathf::Hash22(glm::i32vec2 x)
{
    // 定义一些用于哈希计算的常数
    int prime1 = seed + 61;
    int prime2 = seed + 251;
    int multiplier = seed + 16777213; // 一个较大的质数，用于哈希值的进一步混合

    // 分别计算x和y坐标的哈希值
    int hashX = x.x * prime1; // 可以添加更多的混合步骤，但这里为了简单起见只使用乘法
    int hashY = x.y * prime2; // 同上

    // 可选：为了进一步混合坐标的影响，可以对hashX和hashY进行额外的运算
    // 例如，可以使用位运算、加法、异或等操作
    // 在这个例子中，我们只对hashX进行额外的乘法运算来展示如何添加复杂性
    hashX = (hashX * multiplier) ^ (hashX >> 16);

    // 返回二维向量，其中包含了计算得到的哈希值
    return {hashX, hashY};
}

glm::vec2 Mathf::GetGrad(glm::i32vec2 coords)
{
    glm::vec2 res;
    res = Hash22(coords);
    res = glm::normalize(res);
    return res;
}

float Mathf::Cha(glm::vec2 cor, glm::vec4 ys)
{
    using namespace std;
    float res;
    res = lerp(lerp(ys[2], ys[3],
                    Mathf::Fade(cor.x)),
               lerp(ys[0], ys[1],
                    Mathf::Fade(cor.x)),
               Mathf::Fade(cor.y));
    return res;
}

float Mathf::Noise(float A, uint32_t lsc, float h, glm::i32vec2 cor)
{
    float res;

    // 大晶格方块宽度
    uint32_t blbw = lsc * Section::Size;

    // 大晶格内标准化坐标
    glm::vec2 blnCor = {
            cor.x % blbw / (float) blbw,
            cor.y % blbw / (float) blbw
    };

    // 大晶格 晶格坐标
    glm::i32vec2 blCor = {
            cor.x / blbw * lsc,
            cor.y / blbw * lsc
    };

    // 大晶格四顶点 晶格坐标
    glm::i32vec2 blfvs[4] = {
            {blCor.x,       blCor.y + lsc},
            {blCor.x + lsc, blCor.y + lsc},
            {blCor.x,       blCor.y},
            {blCor.x + lsc, blCor.y},
    };

    // 晶格四顶点高度
    glm::vec4 lfv;
    lfv[0] = GetY(blfvs[0]);
    lfv[1] = GetY(blfvs[1]);
    lfv[2] = GetY(blfvs[2]);
    lfv[3] = GetY(blfvs[3]);

    res = Cha(blnCor, lfv);
    res *= A;
    res += h;
    return res;
}

float Mathf::GetY(glm::i32vec2 cor)
{
    return ((float) (Hash21(cor) % 32)) / 32;
}
