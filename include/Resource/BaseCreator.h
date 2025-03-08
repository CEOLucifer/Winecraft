#pragma once

#include "../Typedef.h"
#include "ArduinoJson.h"

class Resource;

class BaseCreator
{
public:
    virtual ~BaseCreator() = default;

    virtual Sp<Resource> CreateNew(const JsonDocument& doc) { return nullptr; }
};