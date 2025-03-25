#pragma once

#include <glm/glm.hpp>

/// 32位颜色
class Color : public glm::vec4
{
public:
    Color() : glm::vec4(1)
    {
    }

    Color(float r, float g, float b, float a) : glm::vec4(r, g, b, a)
    {}

public:
    static Color Red;
    static Color Green;
    static Color Blue;
    static Color Black;
    static Color White;
    static Color Yellow;
};