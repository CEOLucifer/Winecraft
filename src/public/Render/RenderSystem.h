#pragma once

#include "DirectionalLight.h"
#include "Singleton.h"
#include "SpotLight.h"
#include "Typedef.h"
#include <memory>
#include <vector>

class Renderer;
class Camera;
class GLFWwindow;

class RenderSystem : public Singleton<RenderSystem>
{
    friend class Camera;

private:
    /// @brief 存储所有渲染器
    std::vector<Sp<Renderer>> renderVec;

    /// @brief 摄像机
    std::vector<Sp<Camera>> cameraVec;

    GLFWwindow* window = nullptr;

    /// @brief 点光源
    Sp<SpotLight> spotLight;
    
    /// @brief 定向光
    Sp<DirectionalLight> directionalLight;

public:
    void OnLoad() override;

    void OnUnload() override;

    void onFrameBufferResize(GLFWwindow *window, int w, int h);

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

    void AddCamera(Sp<Camera> camera) { cameraVec.push_back(camera); }

    void RemoveCamera(Sp<Camera> camera)
    {
        for (auto each = cameraVec.begin(); each != cameraVec.end(); each++)
        {
            if (*each == camera)
            {
                cameraVec.erase(each);
                break;
            }
        }
    }
};