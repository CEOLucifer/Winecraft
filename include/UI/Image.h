#pragma once

#include "Control.h"
#include "Render/Color.h"

class Texture;

/// 图片控件
class Image : public Control
{
private:
    Sp<Texture> tex;
    Color color;

public:
    void SetTex(Sp<Texture> value)
    {
        tex = value;
    }

    Sp<Texture> GetTex()
    {
        return tex;
    }

    void SetColor(const Color& value)
    {
        color = value;
    }

    Color& GetColor()
    {
        return color;
    }

    void Awake() override;
};