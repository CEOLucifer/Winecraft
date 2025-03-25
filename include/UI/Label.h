#pragma once


#include "Control.h"
#include "Font/Font.h"
#include "Render/Color.h"

/// 标签。用于渲染UI文本。
class Label : public Control
{
private:
    String text = "New Text";
    Sp<Font> font;
    Color color;
    f32 fontSize = 1;

public:
    String& GetText()
    {
        return text;
    }

    void SetText(const String& value)
    {
        text = value;
    }

    Sp<Font> GetFont()
    {
        return font;
    }

    Color& GetColor()
    {
        return color;
    }

    void SetColor(const Color& value)
    {
        color = value;
    }

    f32 GetFontSize()
    {
        return fontSize;
    }

    void Awake() override;
};