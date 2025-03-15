#pragma once

#include <glm/glm.hpp>

/// 提供常用数学函数，包括种子随机。
class Mathf
{
    friend class App;

private:
    static int seed;

public:
    static int RandomIntRange(int min, int max);

    static float Random01();

    static float RandomFloatRange(float min, float max);

    static glm::vec2 RandomDir2D();

    static int Hash21(glm::i32vec2 x);

    /// 获取指定晶格顶点处的高度
    /// \param coords
    /// \return
    static uint32_t GetHeight(glm::i32vec2 coords);

    //缓和曲线计算权重
    static float Fade(float t)
    {
        //return t * t * (3.0 - 2.0 * t); 使用3t^2−2t^3曲线也是可行的
        return t * t * t * (t * (t * 6 - 15) + 10); // 6t^5-15t^4+10t^3
    }


private:
    static void init();
};