#pragma once

#include "DirectionalLight.h"
#include "Singleton.h"
#include "SpotLight.h"
#include <memory>
#include <vector>
#include <glad/glad.h>

class Renderer;
class Camera;
class GLFWwindow;

class RenderSystem : public Singleton<RenderSystem>
{
    friend class Camera;

private:
    /// @brief 存储所有渲染器
    std::vector<std::shared_ptr<Renderer>> renderVec;
    /// @brief 摄像机
    std::shared_ptr<Camera> camera;
    GLFWwindow* window = nullptr;
    /// @brief 点光源
    std::shared_ptr<SpotLight> spotLight;
    /// @brief 定向光
    std::shared_ptr<DirectionalLight> directionalLight;

public:
    void OnLoad() override;

    void OnUnload() override;

    void onFrameBufferResize(GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    GLFWwindow* GetWindow() { return window; }

    void SetSpotLight(std::shared_ptr<SpotLight> value) { spotLight = value; }



    std::shared_ptr<SpotLight> GetSpotLight() { return spotLight; }

    void SetDirectionalLight(std::shared_ptr<DirectionalLight> value)
    {
        directionalLight = value;
    }

    std::shared_ptr<DirectionalLight> GetDirectionalLight()
    {
        return directionalLight;
    }

    void Render();

    void Add(std::shared_ptr<Renderer> renderer)
    {
        renderVec.push_back(renderer);
        SortAll();
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

    /// @brief 对所有Renderer的渲染顺序排序 
    void SortAll();
};