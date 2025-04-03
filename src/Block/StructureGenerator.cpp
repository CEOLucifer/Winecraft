#include "Block/StructureGenerator.h"
#include "Block/Lattice.h"
#include "Block/BlockSystem.h"
#include "Mathf.h"

void StructureGenerator::CreateTree(i32vec3 bwc)
{
    i32 trunkH = 5;

    // 从(0, 0, 0) bwc，映射到参数bwc
    // 树干
    for (i32 y = 0; y < trunkH; ++y)
    {
        BlockSystem::Instance()->SetBlock(6, {bwc.x, bwc.y + y, bwc.z});
    }

    // 叶子
    i32vec3 offset = {bwc.x, bwc.y + 2, bwc.z};
    vec3 p0 = {0, 0, 0};
    vec3 p1 = {0, 1, 6};
    vec3 p2 = {0, 3, 3};
    vec3 p3 = {0, 5, 0};
    i32 trunkMore = trunkH - offset.y + bwc.y;

    for (i32 y = 0; y <= p3.y; ++y)
    {
        // 半径
        i32 r = Mathf::Bezier((f32) y / p3.y, p0.z, p1.z, p2.z, p3.z);
        for (i32 x = -r; x <= r; ++x)
        {
            for (i32 z = -r; z <= r; ++z)
            {
                if (x * x + z * z > r * r)
                    continue;

                if (x == 0 && z == 0 && y <= trunkMore)
                    continue;

                BlockSystem::Instance()->SetBlock(7, i32vec3{x, y, z} + offset);
            }
        }
    }
}