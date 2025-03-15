#pragma once

#include "Control.h"

class Texture;

/// 图片控件
class Image : public Control
{
private:
    Sp<Texture> tex;

public:
    void SetTex(Sp<Texture> value)
    {
        tex = value;
    }

    Sp<Texture> GetTex()
    {
        return tex;
    }

    void Awake() override;
};