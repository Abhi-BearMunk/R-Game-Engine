#include "RPointLightComponent.h"
#include "Entity.h"
#include "RGame.h"
#include "RLightingManager.h"
#include "RTransformComponent.h"

RPointLightComponent::RPointLightComponent(const std::weak_ptr<REntity> _entity, const RColor& color, const float& radius)
	:RComponent(_entity)
{
	// Set Lighting Manager
	lightingManager = _entity.lock()->GetGame().GetLightingManager();
	// Create point light struct
	index = lightingManager.lock()->AddPointLight();

	// Get refernece to point light
	RPointLight& pointLight = lightingManager.lock()->GetPointLight(index);

	// Set light properties
	pointLight.ambient = glm::vec4(0, 0, 0, 1);
	pointLight.diffuse = color.ToVec4();
	pointLight.specular = color.ToVec4();
	pointLight.constant = 0;
	pointLight.linear = 0;
	pointLight.quadratic = 1 / pow(radius, 2);
}

RPointLightComponent::~RPointLightComponent()
{
	GetEntity().lock()->GetGame().GetLightingManager().lock()->RemovePointLight(index);
}

void RPointLightComponent::Start()
{
}

void RPointLightComponent::Update()
{
	if (GetEntity().lock()->GetComponent<RTransformComponent>().use_count() > 0)
	{
		lightingManager.lock()->GetPointLight(index).position = glm::vec4(GetEntity().lock()->GetComponent<RTransformComponent>().lock()->GetPosition(), 1);
	}
}

void RPointLightComponent::SetAmbient(RColor color) 
{ 
	lightingManager.lock()->GetPointLight(index).ambient = color.ToVec4(); 
}

void RPointLightComponent::SetDiffuse(RColor color) 
{ 
	lightingManager.lock()->GetPointLight(index).diffuse = color.ToVec4(); 
}

void RPointLightComponent::SetSpecular(RColor color) 
{ 
	lightingManager.lock()->GetPointLight(index).specular = color.ToVec4(); 
}

void RPointLightComponent::SetRadius(float radius) 
{ 
	//lightingManager.lock()->GetPointLight(index).linear = 4.48f / radius; 
	//lightingManager.lock()->GetPointLight(index).quadratic = 71.68 / pow(radius, 2); 

	lightingManager.lock()->GetPointLight(index).linear = 0;
	lightingManager.lock()->GetPointLight(index).quadratic = 1 / pow(radius, 2);
}
