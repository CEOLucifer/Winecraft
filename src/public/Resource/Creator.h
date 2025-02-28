#pragma once

#include "BaseCreator.h"
#include <string>
#include "Typedef.h"
#include <ArduinoJson.h>

template<typename T>
class Creator : public BaseCreator
{
public:
    Sp<T> CreateNew(const JsonDocument& doc)
    {
        Sp<T> res(new T);
        res->OnCreated(doc);
        return res;
    }
};