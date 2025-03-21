#include "Block/Lattice.h"

Lattice::Lattice()
{
    // Size * Size
    Sections.resize(Size);
    for (auto& each: Sections)
    {
        each.resize(Size);
        for (auto& section: each)
        {
            section = Section::Create();
        }
    }
}

void Lattice::GenerateRandom(glm::i32vec2 _cor)
{
    cor = _cor;
    for (int xx = 0; xx < Lattice::Size; ++xx)
    {
        for (int zz = 0; zz < Lattice::Size; ++zz)
        {
            Sections[xx][zz]->GenerateRandom({cor.x + xx, cor.y + zz});
        }
    }
}

void Lattice::TransferBufferData()
{
    for(auto each0 : Sections)
    {
        for(auto each1 : each0)
        {
            each1->TransferBufferData();
        }
    }
}
