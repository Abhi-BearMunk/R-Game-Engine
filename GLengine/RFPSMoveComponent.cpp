#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RFPSMoveComponent.h"
#include "Entity.h"
#include "RGame.h"
#include "RWindow.h"
#include "RTransformComponent.h"

RFPSMoveComponent::RFPSMoveComponent(const std::weak_ptr<REntity> _entity, const float& _moveSpeed, const float& _lookSpeed)
	:RComponent(_entity), moveSpeed(_moveSpeed), lookSpeed(_lookSpeed)
{
	glfwGetCursorPos(GetGame().GetGameWindow().window, &mouseX, &mouseY);
}

void RFPSMoveComponent::Start()
{
}

void RFPSMoveComponent::Update()
{
	auto transform = GetEntity().lock()->GetComponent<RTransformComponent>();
	auto window = GetGame().GetGameWindow().window;

	// WASD
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		transform.lock()->SetPosition(transform.lock()->GetPosition() - transform.lock()->Forward() * (1.0f / 60.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		transform.lock()->SetPosition(transform.lock()->GetPosition() + transform.lock()->Forward() * (1.0f / 60.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		transform.lock()->SetPosition(transform.lock()->GetPosition() - transform.lock()->Right() * (1.0f / 60.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		transform.lock()->SetPosition(transform.lock()->GetPosition() + transform.lock()->Right() * (1.0f / 60.0f));
	}

	// Mouse Move
	double currentMouseX, currentMouseY;
	glfwGetCursorPos(GetGame().GetGameWindow().window, &currentMouseX, &currentMouseY);
	float deltaX = currentMouseX - mouseX;
	float deltaY = currentMouseY - mouseY;

	transform.lock()->LookAt(transform.lock()->GetPosition() + transform.lock()->Forward() - lookSpeed * (1.0f / 60.0f) * (deltaX * transform.lock()->Right() - deltaY * transform.lock()->Up()));

	mouseX = currentMouseX;
	mouseY = currentMouseY;

}
