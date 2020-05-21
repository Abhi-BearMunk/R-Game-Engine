#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Texture.h"

RTexture2D::RTexture2D(float _width, float _height, ImageFormat _imageFormat, WrapMode _wrapMode, FilterMode _filterMode)
	:RTexture(_width, _height, _wrapMode, _filterMode)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);


	switch (wrapMode)
	{
	case WrapMode::Clamped:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case WrapMode::Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case WrapMode::Mirrored:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	default:
		break;
	}

	switch (filterMode)
	{
	case FilterMode::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case FilterMode::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	GLuint format = GL_RGBA;
	GLenum type = GL_UNSIGNED_BYTE;

	switch (_imageFormat)
	{
	case ImageFormat::RGB:
		format = GL_RGB;
		break;
	case ImageFormat::RGBA:
		format = GL_RGBA;
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);
}

RTexture2D::RTexture2D(const char* texturePath, bool gammaCorrection, WrapMode _wrapMode, FilterMode _filterMode)
	: RTexture(_wrapMode, _filterMode)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	switch (wrapMode)
	{
	case WrapMode::Clamped:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		break;
	case WrapMode::Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		break;
	case WrapMode::Mirrored:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		break;
	default:
		break;
	}

	switch (filterMode)
	{
	case FilterMode::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case FilterMode::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath, &width, &height, &numberOfChannels, 0);

	GLuint internalFormat = GL_RGBA;
	GLuint format = GL_RGBA;
	GLenum type = GL_UNSIGNED_BYTE;

	switch (numberOfChannels)
	{
	case 1:
		internalFormat = GL_RED;
		format = GL_RGB;
		type = GL_FLOAT;
	case 2:
		internalFormat = GL_RG;
		format = GL_RGB;
	case 3:
		gammaCorrection ? internalFormat = GL_SRGB : internalFormat = GL_RGB;
		format = GL_RGB;
		break;
	case 4:
		gammaCorrection ? internalFormat = GL_SRGB_ALPHA : internalFormat = GL_RGBA;
		break;
	}

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
