#pragma once
#include "RTexture.h"

class RTexture2D : public RTexture
{
public:
    RTexture2D(float _width = 512, float _height = 512, ImageFormat _imageFormat = ImageFormat::RGB, WrapMode _wrapMode = WrapMode::Repeat, FilterMode _filterMode = FilterMode::Linear);
    RTexture2D(const char* texturePath, WrapMode _wrapMode = WrapMode::Clamped, FilterMode _filterMode = FilterMode::Linear );
};

