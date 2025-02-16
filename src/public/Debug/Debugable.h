#pragma once

#include <format>
#include <string>
#include <glm/glm.hpp>

class Debugable
{
public:
    std::string info;

public:
    Debugable(const glm::vec2 value)
    {
        info = std::format("({}, {})", value.x, value.y);
    }
};