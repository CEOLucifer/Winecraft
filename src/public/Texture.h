#pragma once

#include "Resource/Resource.h"
#include "Resource/ResourceFactory.h"
#include <cstdint>
#include <memory>
#include <glad/glad.h>
#include <string>

class Texture : public Resource
{
    friend class TextureFactory;

private:
    uint32_t id;
    std::string type;

public:
    ~Texture() { glDeleteTextures(1, &id); }

    uint32_t GetID() { return id; }
};

class TextureFactory : public ResourceFactory<Texture>
{
public:
    void onCreate(std::shared_ptr<Texture> res, std::string path) override;
};