#pragma once
#include "RTexture.h"

class RCubeMap : public RTexture
{
public:
    RCubeMap(const char* faceTexturePaths[6], WrapMode _wrapMode = WrapMode::Clamped, FilterMode _filterMode = FilterMode::Linear);
};

