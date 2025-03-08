#pragma once

#include "glm/glm.hpp"
#include <iostream>
#include <iomanip>

class BerlinTest
{
private:
    glm::vec2 vertices[4] = {{2,  1},
                             {-1, -2},
                             {1,  -1},
                             {1,  1}};

    float heights[8][8] = {};


public:
    void Run()
    {
        for (int i = 0; i < 4; ++i)
        {
            vertices[i] = glm::normalize(vertices[i]);
        }

        for (int x = 0; x < 8; ++x)
        {
            for (int y = 0; y < 8; ++y)
            {
                glm::vec2 dist[4] = {
                        {x,     y},
                        {x - 8, y},
                        {x - 8, y - 8},
                        {x,     y - 8}
                };

                float influences[4];
                for (int i = 0; i < 4; ++i)
                {
                    influences[i] = glm::dot(vertices[i], dist[i]);
                }

                for (int i = 0; i < 4; ++i)
                {
                    heights[x][y] += influences[i];
                }
            }
        }

        std::cout << std::setprecision(6);
        for (int x = 0; x < 8; ++x)
        {
            for (int y = 0; y < 8; ++y)
            {
                std::cout << std::setw(10) << heights[x][y] << " ";
            }
            std::cout << std::endl;
        }

    }
};