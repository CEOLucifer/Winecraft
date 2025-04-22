#include "Block/Structure.hpp"
#include "ArduinoJson.hpp"
#include "Std/Basic.h"

void Structure::SetSize(u32 _x, u32 _y, u32 _z)
{
    mx = _x;
    my = _y;
    mz = _z;
    blocks.resize(_x * _y * _z, 0);
}

String Structure::Serialize()
{
    using namespace ArduinoJson;
    JsonDocument doc;

    doc["mx"] = mx;
    doc["my"] = my;
    doc["mz"] = mz;

    for (u32 x = 0; x < mx; ++x)
    {
        for (u32 y = 0; y < my; ++y)
        {
            for (u32 z = 0; z < mz; ++z)
            {
                doc["blocks"][x][y][z] = (u32) operator[](x, y, z);
            }
        }
    }
    String res;
    serializeJson(doc, res);
    return res;
}

void Structure::Deserialize(String jsonStr)
{
    using namespace ArduinoJson;
    JsonDocument doc;
    deserializeJson(doc, jsonStr);

    SetSize(doc["mx"], doc["my"], doc["mz"]);

    for (u32 x = 0; x < mx; ++x)
    {
        for (u32 y = 0; y < my; ++y)
        {
            for (u32 z = 0; z < mz; ++z)
            {
                operator[](x, y, z) = (u32)doc["blocks"][x][y][z];
            }
        }
    }
}
