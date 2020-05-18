#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "RCubeMap.h"

RCubeMap::RCubeMap(const char* texturePaths[6], WrapMode _wrapMode, FilterMode _filterMode)
	:RTexture(_wrapMode, _filterMode)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	switch (wrapMode)
	{
	case WrapMode::Clamped:
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		break;
	case WrapMode::Repeat:
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
		break;
	case WrapMode::Mirrored:
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
		break;
	default:
		break;
	}

	switch (filterMode)
	{
	case FilterMode::Linear:
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case FilterMode::Nearest:
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	}

	stbi_set_flip_vertically_on_load(false);

	unsigned char* data;
	for (GLuint i = 0; i < 6; i++)
	{
		const char* path = texturePaths[i];
		data = stbi_load(path, &width, &height, &numberOfChannels, 0);

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
			internalFormat = GL_RGB;
			format = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA;
			break;
		}

		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data
			);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
