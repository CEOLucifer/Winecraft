#pragma once

#include "Control.h"
#include "../Render/Addition.h"

class Renderer;
class Texture;

class Image : public Control
{
    friend class ImageAddition;

private:
    /// @brief 基于的Renderer
    Sp<Renderer> renderer;

    Sp<Texture> texture;

public:
    void Awake() override;

    void OnAdded() override;
};

class ImageAddition : public Addition
{
public:
    Sp<Image> image;

public:
    void Add() override;
};