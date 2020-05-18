#include "RFrameBufferObject.h"

RFrameBufferObject::RFrameBufferObject(int width, int height, FrameBufferObjectType type)
{
	GLenum format = GL_DEPTH24_STENCIL8;
	switch (type)
	{
	case FrameBufferObjectType::R_DEPTH24_STENCIL8:
		format = GL_DEPTH24_STENCIL8;
		break;
	}
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RFrameBufferObject::~RFrameBufferObject()
{
	glDeleteRenderbuffers(1, &ID);
}
