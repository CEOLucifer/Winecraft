#pragma once

#include "Singleton.h"
#include <Render/Renderer.h>
#include <vector>

class RenderSystem : public Singleton<RenderSystem>
{
private:
    std::vector<std::shared_ptr<Renderer>> renderVec;

public:
    void Render(Camera& camera)
    {
        for (auto renderer : renderVec)
        {
            renderer->Draw(camera);
        }
    }

    void Add(std::shared_ptr<Renderer> renderer)
    {
        renderVec.push_back(renderer);
    }

    void Remove(std::shared_ptr<Renderer> renderer)
    {
        for (auto each = renderVec.begin(); each != renderVec.end(); each++)
        {
            if (*each == renderer)
            {
                renderVec.erase(each);
                break;
            }
        }
    }
};