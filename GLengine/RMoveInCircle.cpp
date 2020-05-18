#include "RMoveInCircle.h"
#include "Entity.h"
#include "RTransformComponent.h"

RMoveInCircle::RMoveInCircle(const std::weak_ptr<REntity> _entity, const float& _angularSpeed, const float& _radius, const glm::vec3& _center)
	:RComponent(_entity), angularSpeed(_angularSpeed), radius(_radius), center(_center)
{
}

void RMoveInCircle::Start()
{
}

void RMoveInCircle::Update()
{
	t += 1 / 60.0f;
	theta = glm::radians(angularSpeed * t);
	if (GetEntity().lock()->GetComponent<RTransformComponent>().use_count() > 0)
	{
		GetEntity().lock()->GetComponent<RTransformComponent>().lock()->SetPosition(
			radius * (cos(theta) * glm::vec3(1, 0, 0) + sin(theta) * glm::vec3(0, 0, 1)) + center);
	}
}
