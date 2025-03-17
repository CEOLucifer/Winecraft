#pragma once

#include <glm/glm.hpp>

/// 提供常用数学函数，包括种子随机。
class Mathf
{
    friend class App;

private:
    static int seed;

public:
    static void SetSeed(int value);

    static int RandomIntRange(int min, int max);

    static float Random01();

    static float RandomFloatRange(float min, float max);

    static glm::vec2 RandomDir2D();

    static int Hash21(glm::i32vec2 x);

    static glm::i32vec2 Hash22(glm::i32vec2 x);

    static float Hash_2i_1f01(glm::i32vec2 in);

    /// 获取指定晶格顶点处的高度
    /// \param coords
    /// \return
    static uint32_t GetHeight(glm::i32vec2 coords);

    /// 缓和曲线计算权重
    static float Fade(float t)
    {
//        return t * t * (3.0 - 2.0 * t); // 使用3t^2−2t^3曲线也是可行的
        return t * t * t * (t * (t * 6 - 15) + 10); // 6t^5-15t^4+10t^3
    }

    /// 获取指定晶格顶点处的梯度向量。
    /// \param coords
    /// \return
    static glm::vec2 GetGrad(glm::i32vec2 coords);

    /// 获取晶格内标准化y值
    /// \param cor 标准化晶格内坐标
    /// \param ys 晶格四顶点y值
    static float Cha(glm::vec2 cor, glm::vec4 ys);

    /// 获取指定晶格顶点的y值
    /// \param cor
    static float GetY(glm::i32vec2 cor);

    /// 获取指定世界坐标下的y值
    /// \param A 振幅。
    /// \param lw 晶格宽度。相当于周期。
    /// \param h 整体高度抬升值。
    /// \param cor 世界xz坐标
    static float Noise(float A, uint32_t lw, float h, glm::i32vec2 cor);

private:
    /// 初始化，用于配置种子
    static void init();
};