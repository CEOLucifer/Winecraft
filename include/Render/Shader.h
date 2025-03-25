#pragma once

#include <cstddef>
#include <cstdint>
#include "Resource/Resource.h"

class Shader : public Resource
{
    friend class ShaderFactory;

private:
    uint32_t id;

public:
    ~Shader();

    uint32_t GetID() { return id; }

    void OnResourceCreation(const JsonDocument& doc) override;
};