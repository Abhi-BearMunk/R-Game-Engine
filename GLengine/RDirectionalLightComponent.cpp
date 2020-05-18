#include "RDirectionalLightComponent.h"
#include "Entity.h"
#include "RGame.h"
#include "RLightingManager.h"
#include "RTransformComponent.h"

RDirectionalLightComponent::RDirectionalLightComponent(const std::weak_ptr<REntity> _entity, const RColor& color)
	:RComponent(_entity)
{
	// Set Lighting Manager
	lightingManager = _entity.lock()->GetGame().GetLightingManager();
	// Create point light struct
	index = lightingManager.lock()->AddDirectionalLight();

	// Get refernece to point light
	RDirLight& dirLight = lightingManager.lock()->GetDirectionalLight(index);

	// Set light properties
	dirLight.ambient = color.ToVec4() * 0.1f;
	dirLight.diffuse = color.ToVec4();
	dirLight.specular = color.ToVec4();
}

RDirectionalLightComponent::~RDirectionalLightComponent()
{
	GetEntity().lock()->GetGame().GetLightingManager().lock()->RemoveDirectionalLight(index);
}

void RDirectionalLightComponent::Start()
{
}

void RDirectionalLightComponent::Update()
{
	if (GetEntity().lock()->GetComponent<RTransformComponent>().use_count() > 0)
	{
		lightingManager.lock()->GetDirectionalLight(index).direction = glm::vec4(GetEntity().lock()->GetComponent<RTransformComponent>().lock()->Forward(), 0);
	}
}

void RDirectionalLightComponent::SetAmbient(RColor color)
{
	lightingManager.lock()->GetDirectionalLight(index).ambient = color.ToVec4();
}

void RDirectionalLightComponent::SetDiffuse(RColor color)
{
	lightingManager.lock()->GetDirectionalLight(index).diffuse = color.ToVec4();
}

void RDirectionalLightComponent::SetSpecular(RColor color)
{
	lightingManager.lock()->GetDirectionalLight(index).specular = color.ToVec4();
}
