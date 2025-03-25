#pragma once

#include "Resource/Resource.h"
#include "Std/Basic.h"
#include "Character.h"

/// 字体
class Font : public Resource
{
private:
    /// 存储该字体的所有字形
    Map<u8, Character> characterMap;

public:
    ~Font() override;

    void OnResourceCreation(const JsonDocument& doc) override;

    Character& GetCharacter(u8 c)
    {
        return characterMap[c];
    }
};