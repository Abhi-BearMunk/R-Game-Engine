#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RLightingManager.h"
#include "RPointLightComponent.h"

RLightingManager::RLightingManager()
	:uboDirLights(0), uboPointLights(0)
{
	dirLights.reserve(MAX_DIR_LIGHTS);
	pointLights.reserve(MAX_POINT_LIGHTS);
}

void RLightingManager::Init()
{
	glGenBuffers(1, &uboDirLights);
	glGenBuffers(1, &uboPointLights);

	// Dir lights
	glBindBuffer(GL_UNIFORM_BUFFER, uboDirLights);
	glBufferData(GL_UNIFORM_BUFFER, MAX_DIR_LIGHTS * sizeof(RDirLight) + sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, uboDirLights, 0, MAX_DIR_LIGHTS * sizeof(RDirLight) + sizeof(unsigned int));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Point lights
	glBindBuffer(GL_UNIFORM_BUFFER, uboPointLights);
	glBufferData(GL_UNIFORM_BUFFER, MAX_POINT_LIGHTS * sizeof(RPointLight) + sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 2, uboPointLights, 0, MAX_POINT_LIGHTS * sizeof(RPointLight) + sizeof(unsigned int));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void RLightingManager::Update()
{
	// Dir lights
	numDirLights = dirLights.size();
	glBindBuffer(GL_UNIFORM_BUFFER, uboDirLights);
	if (dirLights.size() > 0)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, dirLights.size() * sizeof(RDirLight), &dirLights[0]);
	}
	glBufferSubData(GL_UNIFORM_BUFFER, MAX_DIR_LIGHTS * sizeof(RDirLight), sizeof(unsigned int), &numDirLights);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Point lights
	numPointLights = pointLights.size();
	glBindBuffer(GL_UNIFORM_BUFFER, uboPointLights);
	if (pointLights.size() > 0)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, pointLights.size() * sizeof(RPointLight), &pointLights[0]);
	}
	glBufferSubData(GL_UNIFORM_BUFFER, MAX_POINT_LIGHTS * sizeof(RPointLight), sizeof(unsigned int), &numPointLights);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

unsigned int RLightingManager::AddDirectionalLight()
{
	dirLights.emplace_back();
	return dirLights.size() - 1;
}

void RLightingManager::RemoveDirectionalLight(unsigned int index)
{
	dirLights.erase(dirLights.begin() + index);
}

unsigned int RLightingManager::AddPointLight()
{
	pointLights.emplace_back();
	return pointLights.size() - 1;
}

void RLightingManager::RemovePointLight(unsigned int index)
{
	pointLights.erase(pointLights.begin() + index);
}
