#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class RMoveInCircle :
	public RComponent
{
public:
	RMoveInCircle(const std::weak_ptr<REntity> _entity, const float& _angularSpeed = 90, const float& _radius = 1, const glm::vec3& _center = glm::vec3(0, 0, 0));
	float radius;
	float angularSpeed;
	glm::vec3 center;
	void Start();
	void Update();
private:
	float t = 0;
	float theta = 0;
};

