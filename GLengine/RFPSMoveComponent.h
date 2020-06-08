#pragma once
#include <memory>
#include "Component.h"

class REntity;
class RFPSMoveComponent :
	public RComponent
{
public:
	RFPSMoveComponent(const std::weak_ptr<REntity> _entity, const float& moveSpeed = 5, const float& lookSpeed = 0.1f);
	void Start();
	void Update();
	float moveSpeed;
	float lookSpeed;
private:
	double mouseX;
	double mouseY;
	float pitch;
	float yaw;
};

