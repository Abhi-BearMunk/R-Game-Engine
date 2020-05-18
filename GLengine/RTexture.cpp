#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RTexture.h"

RTexture::RTexture(WrapMode _wrapMode, FilterMode _filterMode)
	: wrapMode(_wrapMode), filterMode(_filterMode)
{
}

RTexture::RTexture(float _width, float _height, WrapMode _wrapMode, FilterMode _filterMode)
	:width(_width), height(_height), wrapMode(_wrapMode), filterMode(_filterMode)
{
}

RTexture::~RTexture()
{
	glDeleteTextures(1, &ID);
}
