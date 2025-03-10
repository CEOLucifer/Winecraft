#include "Block/Section.h"

void Section::FillWith(Block block)
{
    for (int x = 0; x < 32; ++x)
    {
        for (int y = 0; y < 32; ++y)
        {
            for (int z = 0; z < 32; ++z)
            {
                Blocks[x][y][z] = block;
            }
        }
    }
}
