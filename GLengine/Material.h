#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <memory>

class RTexture;
class RMaterial
{
public:
	RMaterial(const char* vertexShaderPath, const char* fragmentShaderPath);
	~RMaterial();
	void Activate() const;
	void Use() const;
	void SetTexture(const std::string& name, std::shared_ptr<RTexture> texture);
	inline void SetMat4(const std::string& name, glm::mat4 value) const { glUseProgram(ID); glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); }
	inline void SetInt(const std::string& name, int value) const { glUseProgram(ID); glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
	inline void SetFloat(const std::string& name, float value) const { glUseProgram(ID); glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }
	inline void SetVec2(const std::string& name, glm::vec2 value) const { glUseProgram(ID); glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y); }
	inline void SetVec3(const std::string& name, glm::vec3 value) const { glUseProgram(ID); glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); }
	inline void SetVec4(const std::string& name, glm::vec4 value) const { glUseProgram(ID); glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w); }

	// Render queue
	unsigned int renderQueue = 2000;

	// Transparency
	bool alpha = false;
	GLenum blendFuncSrc = GL_SRC_ALPHA;
	GLenum blendFuncDest = GL_ONE_MINUS_SRC_ALPHA;

	// Stencil
	GLenum stencilFunc = GL_ALWAYS;
	GLint stencilRef = 0;
	GLuint stencilMask = 0XFF;
	GLenum stencilFail = GL_KEEP;
	GLenum stencilPassDepthFail = GL_KEEP;
	GLenum stencilDepthPass = GL_KEEP;

	// Depth
	GLenum depthFunc = GL_LESS;
	GLenum depthMask = GL_TRUE;
private:
	unsigned int ID;
	void checkCompileErrors(unsigned int shader, std::string type);
	std::map<const std::string, std::shared_ptr<RTexture>> textures;	
};

