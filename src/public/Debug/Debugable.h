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

    Debugable(const glm::vec3 value)
    {
        info = std::format("({}, {}, {})", value.x, value.y, value.z);
    }

    Debugable(const std::string& value) { info = value; }

    Debugable(const char* value) { info = value; }

    Debugable(auto value) { info = std::format("{}", value); }
};