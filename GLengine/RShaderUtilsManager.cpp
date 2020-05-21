#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>
#include "RShaderUtilsManager.h"

void RShaderUtilsManager::Init()
{
	// Create Camera UBO for shaders
	glGenBuffers(1, &utilsUBO);

	glBindBuffer(GL_UNIFORM_BUFFER, utilsUBO);
	glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 5, utilsUBO, 0, sizeof(glm::vec4));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void RShaderUtilsManager::Update()
{
	glBindBuffer(GL_UNIFORM_BUFFER, utilsUBO);
	float time = glfwGetTime();

	glm::vec4 R_Time = glm::vec4(time * 0.05, time, time * 2, time * 3);
	glm::vec4 R_SinTime = glm::vec4(sin(time / 8), sin(time / 4), sin(time / 2), sin(time));
	glm::vec4 R_CosTime = glm::vec4(cos(time / 8), cos(time / 4), cos(time / 2), cos(time));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(R_Time));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(R_SinTime));
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(R_CosTime));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
