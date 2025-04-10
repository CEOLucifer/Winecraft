#pragma once

#include "DirectionalLight.h"
#include "Singleton.h"
#include "SpotLight.h"
#include "Std/SmartPtr.h"
#include "glm/glm.hpp"
#include <memory>
#include <vector>

class Renderer;

class Camera;

class GLFWwindow;

class Material;

class RenderPass;

class RenderSystem : public Singleton<RenderSystem>
{
    friend class Camera;

    friend class Renderer;

private:
    /// 所有渲染通道
    std::vector<Sp<RenderPass>> renderPassVec;

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

    void onFrameBufferResize(GLFWwindow* window, int w, int h);

    GLFWwindow* GetWindow()
    { return window; }

    glm::vec2 GetWindowSize();

    void SetSpotLight(Sp<SpotLight> value)
    { spotLight = value; }

    Sp<SpotLight> GetSpotLight()
    { return spotLight; }

    void SetDirectionalLight(Sp<DirectionalLight> value)
    {
        directionalLight = value;
    }

    Sp<DirectionalLight> GetDirectionalLight()
    {
        return directionalLight;
    }

    void Render();

    void Add(Sp<RenderPass> renderPass)
    {
        renderPassVec.push_back(renderPass);
        SortRenderOrder();
    }

    void Remove(Sp<RenderPass> renderPass)
    {
        for (auto each = renderPassVec.begin(); each != renderPassVec.end(); each++)
        {
            if (*each == renderPass)
            {
                renderPassVec.erase(each);
                break;
            }
        }
    }

    void AddCamera(Sp<Camera> camera)
    { cameraVec.push_back(camera); }

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

    Sp<Camera> GetFirstCamera()
    {
        if (cameraVec.size() > 0)
        {
            return cameraVec[0];
        }
        return nullptr;
    }

    void SortRenderOrder();
};