#pragma once

#include "BaseCreator.h"
#include "Typedef.h"
#include <ArduinoJson.h>

template <typename T> class Creator : public BaseCreator
{
public:
    Sp<Resource> CreateNew(const JsonDocument& doc) override
    {
        return _createNew(doc);
    }

    Sp<T> _createNew(const JsonDocument& doc)
    {
        Sp<T> res(new T);
        res->OnCreated(doc);
        return res;
    }
};