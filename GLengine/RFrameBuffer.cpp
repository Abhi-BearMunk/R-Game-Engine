#include "RFrameBuffer.h"
#include "Texture.h"
#include "RFrameBufferObject.h"

RFrameBuffer::RFrameBuffer()
{
	glGenFramebuffers(1, &ID);
}

RFrameBuffer::RFrameBuffer(int width, int height, ImageFormat _imageFormat, FrameBufferObjectType fboType)
{
	glGenFramebuffers(1, &ID);

	Activate();

	// Generate Color Buffer
	colorBufferTex = std::make_shared<RTexture2D>(width, height, _imageFormat);
	SetColorBuffer(colorBufferTex);

	// Generate Depth Buffer
	if (fboType != FrameBufferObjectType::R_NONE)
	{
		depthStencilBuffer = std::make_shared<RFrameBufferObject>(width, height, fboType);
		SetDepthBuffer(depthStencilBuffer);
	}
}

RFrameBuffer::~RFrameBuffer()
{
	glDeleteFramebuffers(1, &ID);
}

void RFrameBuffer::SetDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RFrameBuffer::SetColorBuffer(std::shared_ptr<RTexture2D> texture)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->GetID(), 0);
}

void RFrameBuffer::SetDepthBuffer(std::shared_ptr<RFrameBufferObject> fbo)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fbo->GetID());
}

bool RFrameBuffer::IsComplete()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	GLenum complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return complete == GL_FRAMEBUFFER_COMPLETE;
}
