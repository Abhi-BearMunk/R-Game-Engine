#pragma once
#include <glm/glm.hpp>
#include "Component.h"
#include "RColor.h"
#include "LightData.h"

class REntity;
class RLightingManager;
class RDirectionalLightComponent :
	public RComponent
{
public:
	RDirectionalLightComponent(const std::weak_ptr<REntity> _entity, const RColor& color);
	virtual ~RDirectionalLightComponent();

	void Start();
	void Update();

	void SetAmbient(RColor color);
	void SetDiffuse(RColor color);
	void SetSpecular(RColor color);

private:
	unsigned int index;
	std::weak_ptr<RLightingManager> lightingManager;
};

