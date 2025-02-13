#pragma once

#include "Singleton.h"
#include "SpotLight.h"
#include <Render/Renderer.h>
#include <memory>
#include <vector>

class Camera;
class GLFWwindow;

class RenderSystem : public Singleton<RenderSystem>
{
    friend class Camera;

private:
    std::vector<std::shared_ptr<Renderer>> renderVec;
    std::shared_ptr<Camera> camera;
    GLFWwindow* window = nullptr;
    std::shared_ptr<SpotLight> spotLight;

public:
    void OnLoad() override;

    void OnUnload() override;

    void onFrameBufferResize(GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    GLFWwindow* GetWindow() { return window; }

    void SetSpotLight(std::shared_ptr<SpotLight> value) { spotLight = value; }

    void Render()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto renderer : renderVec)
        {
            renderer->Draw(*camera.get());
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