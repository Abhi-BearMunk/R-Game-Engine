#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "REnums.h"

class RTexture2D;
class RFrameBufferObject;
class RFrameBuffer
{
public:
	RFrameBuffer();
	RFrameBuffer(int width, int height, ImageFormat _imageFormat = ImageFormat::RGB, FrameBufferObjectType fboType = FrameBufferObjectType::R_DEPTH24_STENCIL8);
	~RFrameBuffer();
	inline void Activate() { glBindFramebuffer(GL_FRAMEBUFFER, ID); }
	static void SetDefault();
	static void SetColorBuffer(std::shared_ptr<RTexture2D> texture);
	static void SetDepthBuffer(std::shared_ptr<RFrameBufferObject> fbo);
	bool IsComplete();
	inline const unsigned int& GetID() { return ID; }
	inline std::weak_ptr<RTexture2D> GetColorBufferTexture() { return colorBufferTex; }
	inline std::weak_ptr<RFrameBufferObject> GetDepthStencilBuffer() { return depthStencilBuffer; }
private:
	unsigned int ID;
	std::shared_ptr<RTexture2D> colorBufferTex;
	std::shared_ptr<RFrameBufferObject> depthStencilBuffer;
};

