#pragma once
#include <glm/glm.hpp>
#include "Component.h"
#include "RColor.h"
#include "LightData.h"

class REntity;
class RLightingManager;
class RPointLightComponent :
	public RComponent
{
public:
	RPointLightComponent(const std::weak_ptr<REntity> _entity, const RColor& color, const float& radius);
	virtual ~RPointLightComponent();

	void Start();
	void Update();

	void SetAmbient(RColor color);
	void SetDiffuse(RColor color);
	void SetSpecular(RColor color);
	void SetRadius(float radius);

private:
	unsigned int index;
	std::weak_ptr<RLightingManager> lightingManager;
};

