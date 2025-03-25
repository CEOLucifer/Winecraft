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
//    SetSeed(std::time(0));
    SetSeed(666666);
    Debug::Log(std::format("init seed: {}", seed));
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

float Mathf::Noise(float A, uint32_t lw, float h, glm::i32vec2 bwc)
{
    float res;

    // 晶格新坐标
    glm::i32vec2 q = {
            floor(bwc.x / lw),
            floor(bwc.y / lw)
    };

    // 晶格内标准化坐标
    glm::vec2 lnCor = {
            bwc.x % lw / (float) lw,
            bwc.y % lw / (float) lw
    };

    // 晶格 世界坐标
    glm::i32vec2 lCor = {
            q.x * lw,
            q.y * lw
    };

    // 晶格四顶点 世界坐标
    glm::i32vec2 lfvs[4] = {
            {lCor.x,      lCor.y + lw},
            {lCor.x + lw, lCor.y + lw},
            {lCor.x,      lCor.y},
            {lCor.x + lw, lCor.y},
    };

    // 晶格四顶点高度
    glm::vec4 lfv;
    lfv[0] = GetY(lfvs[0]);
    lfv[1] = GetY(lfvs[1]);
    lfv[2] = GetY(lfvs[2]);
    lfv[3] = GetY(lfvs[3]);

    res = Cha(lnCor, lfv);
    res *= A;
    res += h;
    return res;
}

float Mathf::GetY(glm::i32vec2 cor)
{
    return Hash_2i_1f01(cor);
}

void Mathf::SetSeed(int value)
{
    seed = value;
    std::srand(value);
}

float Mathf::Hash_2i_1f01(glm::i32vec2 in)
{
    // 一个简单的哈希算法，将输入组合并使用种子
    uint32_t hash = static_cast<uint32_t>(in.x) * 73856093;
    hash ^= static_cast<uint32_t>(in.y) * 19349663;
    hash ^= static_cast<uint32_t>(seed) * 83492791;

    // 使用哈希值生成一个 0 到 1 之间的浮点数
    return static_cast<float>(hash % 1000000) / 1000000.0f;
}
