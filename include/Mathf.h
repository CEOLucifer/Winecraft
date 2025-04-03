#pragma once

#include <glm/glm.hpp>
#include "Std/Basic.h"
#include "Std/Math.h"

/// 提供常用数学函数，包括种子随机。
class Mathf
{
    friend class App;

private:
    static i32 seed;

public:
    static void SetSeed(i32 value);

    static i32 RandomIntRange(i32 min, i32 max);

    static f32 Random01();

    static f32 RandomFloatRange(f32 min, f32 max);

    static vec2 RandomDir2D();

    static i32 Hash21(i32vec2 x);

    static i32vec2 Hash22(i32vec2 x);

    static f32 Hash_2i_1f01(i32vec2 in);

    /// 获取指定晶格顶点处的高度
    /// \param coords
    /// \return
    static u32 GetHeight(i32vec2 coords);

    /// 缓和曲线计算权重
    static f32 Fade(f32 t)
    {
//        return t * t * (3.0 - 2.0 * t); // 使用3t^2−2t^3曲线也是可行的
        return t * t * t * (t * (t * 6 - 15) + 10); // 6t^5-15t^4+10t^3
    }

    /// 获取指定晶格顶点处的梯度向量。
    /// \param coords
    /// \return
    static vec2 GetGrad(i32vec2 coords);

    /// 获取晶格内标准化y值
    /// \param cor 标准化晶格内坐标
    /// \param ys 晶格四顶点标准化y值
    static f32 Cha(vec2 cor, vec4 ys);

    /// 获取指定晶格顶点的标准化y值
    /// \param cor
    static f32 GetY(i32vec2 cor);

    /// 获取指定世界坐标下的y值。Value噪声。
    /// \param A 振幅。
    /// \param lw 晶格宽度。相当于周期。
    /// \param h 整体高度抬升值。
    /// \param bwc 方块世界xz坐标
    static f32 Noise(f32 A, u32 lw, f32 h, i32vec2 bwc);

    static f32 Bezier(f32 t, f32 p0, f32 p1, f32 p2, f32 p3);

private:
    /// 初始化，用于配置种子
    static void init();
};