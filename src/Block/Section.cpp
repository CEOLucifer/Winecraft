#include "Block/Section.h"

void Section::FillWith(Block block)
{
    for (int x = 0; x < Size; ++x)
    {
        for (int y = 0; y < Height; ++y)
        {
            for (int z = 0; z < Size; ++z)
            {
                Blocks[x][y][z] = block;
            }
        }
    }
}
