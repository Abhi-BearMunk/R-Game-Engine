#pragma once
#include <vector>
#include <memory>
#include "LightData.h"

#define MAX_DIR_LIGHTS 100
#define MAX_POINT_LIGHTS 100

class RLightingManager
{
public:
	RLightingManager();
	void Init();
	void Update();

	// Directional Lights
	unsigned int AddDirectionalLight();
	inline RDirLight& GetDirectionalLight(const unsigned int& index) { return dirLights[index]; }
	void RemoveDirectionalLight(unsigned int index);

	// Point Lights
	unsigned int AddPointLight();
	inline RPointLight& GetPointLight(const unsigned int& index) { return pointLights[index]; }
	void RemovePointLight(unsigned int index);
private:
	// Directional lights
	std::vector<RDirLight> dirLights;
	unsigned int numDirLights;
	unsigned int uboDirLights;

	// Point lights
	std::vector<RPointLight> pointLights;
	unsigned int numPointLights;
	unsigned int uboPointLights;
};

