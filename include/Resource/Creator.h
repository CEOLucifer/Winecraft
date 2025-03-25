#pragma once

#include "BaseCreator.h"
#include "Std/SmartPtr.h"
#include "ArduinoJson.h"
#include "../Core/Object.h"

template <typename T> class Creator : public BaseCreator
{
public:
    Sp<Resource> CreateNew(const JsonDocument& doc) override
    {
        return _createNew(doc);
    }

    Sp<T> _createNew(const JsonDocument& doc)
    {
        Sp<T> res = Object::NewObject<T>();
        res->OnResourceCreation(doc);
        return res;
    }
};