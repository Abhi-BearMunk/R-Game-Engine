#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "REnums.h"

class RFrameBufferObject
{
public:
	RFrameBufferObject(int width = 1280, int height = 720, FrameBufferObjectType format = FrameBufferObjectType::R_DEPTH24_STENCIL8);
	~RFrameBufferObject();
	inline const unsigned int& GetID() { return ID; }
private:
	unsigned int ID;
};

