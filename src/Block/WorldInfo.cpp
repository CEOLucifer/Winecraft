#include "Block/WorldInfo.h"
#include "Mathf.h"

u32 WorldInfo::GetHeight(i32vec2 bwc)
{
    // 高度
    u32 height = 0;
    f32 fHeight = 0;

    // 分形噪声：叠加不同振幅和周期的噪声。
    fHeight += Mathf::Noise(32, 64, 10, bwc);
    fHeight += Mathf::Noise(18, 32, 0, bwc);
    fHeight += Mathf::Noise(2, 8, -1, bwc);

    height = fHeight;

    return height;
}

f32 WorldInfo::GetTemperature(i32vec2 bwc)
{
    return Mathf::Noise(1, 256, 0, bwc);
}

f32 WorldInfo::GetTreeRate(i32vec2 bwc)
{
    return Mathf::Hash_2i_1f01(bwc);
}

f32 WorldInfo::GetCactusRate(i32vec2 bwc)
{
    return Mathf::Hash_2i_1f01(bwc);
}
