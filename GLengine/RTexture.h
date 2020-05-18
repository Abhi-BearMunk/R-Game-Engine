#pragma once
#include "REnums.h"

class RTexture
{
public:
    RTexture(WrapMode _wrapMode = WrapMode::Repeat, FilterMode _filterMode = FilterMode::Linear);
    RTexture(float _width = 512, float _height = 512, WrapMode _wrapMode = WrapMode::Repeat, FilterMode _filterMode = FilterMode::Linear);
    virtual ~RTexture();
    inline const int& GetID() const { return ID; }
protected:
    unsigned int ID = 0;
    int width;
    int height;
    int numberOfChannels;
    WrapMode wrapMode;
    FilterMode filterMode;
};

