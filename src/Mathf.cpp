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

float Mathf::Noise(float A, i32 lw, float h, i32vec2 bwc)
{
    float res;

    // 晶格新坐标
    i32vec2 sswc = {
            bwc.x / lw,
            bwc.y / lw
    };

    // 晶格内标准化坐标
    vec2 nsc = {
            bwc.x % lw / (float) lw,
            bwc.y % lw / (float) lw
    };

    // 负坐标修正
    if (bwc.x < 0)
    {
        sswc.x -= 1;
        nsc.x = 1 + nsc.x;
    }

    if (bwc.y < 0)
    {
        sswc.y -= 1;
        nsc.y = 1 + nsc.y;
    }

    // 晶格 世界坐标
    i32vec2 sbwc = {
            sswc.x * lw,
            sswc.y * lw
    };

    // 晶格四顶点 世界坐标
    i32vec2 lfvs[4] = {
            {sbwc.x,      sbwc.y + lw},
            {sbwc.x + lw, sbwc.y + lw},
            {sbwc.x,      sbwc.y},
            {sbwc.x + lw, sbwc.y},
    };



    // 晶格四顶点高度
    vec4 lfv;
    lfv[0] = GetY(lfvs[0]);
    lfv[1] = GetY(lfvs[1]);
    lfv[2] = GetY(lfvs[2]);
    lfv[3] = GetY(lfvs[3]);

    res = Cha(nsc, lfv);
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

f32 Mathf::Hash_2i_1f01(glm::i32vec2 in)
{
    // 一个简单的哈希算法，将输入组合并使用种子
    uint32_t hash = static_cast<uint32_t>(in.x) * 73856093;
    hash ^= static_cast<uint32_t>(in.y) * 19349663;
    hash ^= static_cast<uint32_t>(seed) * 83492791;

    // 使用哈希值生成一个 0 到 1 之间的浮点数
    return static_cast<float>(hash % 1000000) / 1000000.0f;
}

f32 Mathf::Hash_3i_1f01(i32vec3 in)
{
    // 一个简单的哈希算法，将输入组合并使用种子
    uint32_t hash = static_cast<uint32_t>(in.x) * 73856093;
    hash ^= static_cast<uint32_t>(in.y) * 19349663;
    hash ^= static_cast<uint32_t>(in.z) * 35967396;
    hash ^= static_cast<uint32_t>(seed) * 83492791;

    // 使用哈希值生成一个 0 到 1 之间的浮点数
    return static_cast<float>(hash % 1000000) / 1000000.0f;

}

f32 Mathf::Bezier(f32 t, f32 p0, f32 p1, f32 p2, f32 p3)
{
    return p0 * (1 - t) * (1 - t) * (1 - t) +
           3 * p1 * t * (1 - t) * (1 - t) +
           3 * p2 * t * t * (1 - t) +
           p3 * t * t * t;
}

f32 Mathf::Line3D(f32 m, f32 n, f32 p, f32 x0, f32 y0, f32 z0, f32 x, f32 z)
{
    f32 a;
    if (m == 0)
    {
        a = 0;
    }
    else
    {
        a = p / m;
    }

    f32 b;
    if (n == 0)
    {
        b = 0;
    }
    else
    {
        b = p / n;
    }

    return a * x + b * z + (y0 - a * x0 - b * z0);
}

f32 Mathf::Cos(vec3 a, vec3 b)
{
    return a.length() * b.length() / glm::dot(a, b);
}

f32 Mathf::Cha3D(vec3 cor, const Array<f32, 8>& values)
{
    return std::lerp(Cha({cor.x, cor.z}, {values[0], values[1], values[2], values[3]}),
                     Cha({cor.x, cor.z}, {values[4], values[5], values[6], values[7]}),
                     Mathf::Fade(cor.y));
}

f32 Mathf::Noise3D(f32 A, i32 lw, f32 h, i32vec3 bwc)
{
    f32 res;

    // 晶格新坐标
    i32vec3 sswc = {
            bwc.x / lw,
            bwc.y / lw,
            bwc.z / lw
    };

    // 晶格内标准化坐标
    vec3 nsc = {
            bwc.x % lw / (f32) lw,
            bwc.y % lw / (f32) lw,
            bwc.z % lw / (f32) lw
    };

    // 负坐标修正
    if (bwc.x < 0)
    {
        sswc.x -= 1;
        nsc.x = 1 + nsc.x;
    }

    if (bwc.y < 0)
    {
        sswc.y -= 1;
        nsc.y = 1 + nsc.y;
    }

    if (bwc.z < 0)
    {
        sswc.z -= 1;
        nsc.z = 1 + nsc.z;
    }

    // 晶格 世界坐标
    i32vec3 sbwc = {
            sswc.x * lw,
            sswc.y * lw,
            sswc.z * lw,
    };

    // 晶格八顶点 世界坐标
    i32vec3 lfvs[8] = {
            {sbwc.x,      sbwc.y,      sbwc.z + lw},
            {sbwc.x + lw, sbwc.y,      sbwc.z + lw},
            {sbwc.x,      sbwc.y,      sbwc.z},
            {sbwc.x + lw, sbwc.y,      sbwc.z},
            {sbwc.x,      sbwc.y + lw, sbwc.z + lw},
            {sbwc.x + lw, sbwc.y + lw, sbwc.z + lw},
            {sbwc.x,      sbwc.y + lw, sbwc.z},
            {sbwc.x + lw, sbwc.y + lw, sbwc.z},
    };

    // 晶格八顶点值
    Array<f32, 8> lfv;
    for (i32 i = 0; i < 8; ++i)
    {
        lfv[i] = GetY3D(lfvs[i]);
    }

    res = Cha3D(nsc, lfv);
    res *= A;
    res += h;
    return res;
}

f32 Mathf::GetY3D(i32vec3 cor)
{
    return Hash_3i_1f01(cor);
}