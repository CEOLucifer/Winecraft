#pragma once

#include "ResourceSystem.h"
#include <string>

class Resource
{
    template<typename T>
    friend class ResourceFactory;

private:
    std::string path;

public:
    virtual ~Resource() {}

    const std::string& GetPath() { return path; }
};