#pragma once

#include "Std/Vec.h"
#include "Section.h"

/// 网格
class Lattice
{
public:
    // 区块的长宽数，规定：奇数。
    static constexpr u32 Size = 31;

public:
    Vec<Vec<Sp<Section>>> Sections;

private:
    glm::i32vec2 cor = {0, 0};

public:
    Lattice();

    glm::i32vec2 GetCenterSectionCor()
    {
        return {cor.x + Lattice::Size / 2, cor.y + Lattice::Size / 2};
    }

    void SetCenterSectionCor(glm::i32vec2 value)
    {
        cor = {value.x - Size / 2, value.y - Size / 2};
    }

    void GenerateRandom(glm::i32vec2 cor);

    void TransferBufferData();

    glm::i32vec2 GetCor()
    {
        return cor;
    }

    void SetCor(glm::i32vec2 value)
    {
        cor = value;
    }
};