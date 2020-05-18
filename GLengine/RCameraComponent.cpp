#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "RGame.h"
#include "RWindow.h"
#include "RMesh.h"
#include "Material.h"
#include "RCubeMap.h"
#include "MeshUtil.h"
#include "RTransformComponent.h"
#include "RCameraComponent.h"


RCameraComponent::RCameraComponent(const std::weak_ptr<REntity> _entity, const float& fov, const float& near, const float& far)
	:RComponent(_entity), fieldOfView(fov), nearPlane(near), farPlane(far)
{
	CalculateProjectionMat();
}

void RCameraComponent::Start()
{
	// Create Camera UBO for shaders
	glGenBuffers(1, &cameraUBO);

	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4) + 4 * sizeof(glm::mat4) + 2 * sizeof(float), NULL, GL_STATIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, cameraUBO, 0, 2 * sizeof(glm::vec4) + 4 * sizeof(glm::mat4) + 2 * sizeof(float));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	// Create Skybox
	skyMesh = std::make_shared<RMesh>();
	MeshUtil::CreatePrimitive(MeshUtil::PrimitiveType::Cube, skyMesh);
	const char* faceTexturePaths[6] = {
		"Assets/skybox/right.jpg",
		"Assets/skybox/left.jpg",
		"Assets/skybox/top.jpg",
		"Assets/skybox/bottom.jpg",
		"Assets/skybox/front.jpg",
		"Assets/skybox/back.jpg"
	};
	defaultSkybox = std::make_shared<RCubeMap>(faceTexturePaths);
	skyboxMaterial = std::make_shared<RMaterial>("Shaders/SkyboxVertex.vs", "Shaders/SkyboxFrag.fs");
	//skyboxMaterial->renderQueue = 5000;
	skyboxMaterial->SetTexture("skybox", defaultSkybox);
}

void RCameraComponent::Update()
{
	// TODO : To be fixed later with even system and an event from transform component 
	if (!GetEntity().lock()->GetComponent<RTransformComponent>().expired())
	{
		// Calculate Matrices
		auto transform = GetEntity().lock()->GetComponent<RTransformComponent>().lock();
		viewMat = transform->GetUnscaledWorldToLocalMatrix();
		viewProjectionMat = projectionMat * viewMat;
		invViewProjectionMat = glm::inverse(viewProjectionMat);
		auto position = glm::vec4(transform->GetPosition(), 1);
		// Update shaders params
		glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(position));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(glm::vec4(transform->Forward(), 0)));
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::mat4), glm::value_ptr(projectionMat));
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4) + sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMat));
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4) + 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewProjectionMat));
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4) + 3 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(invViewProjectionMat));
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4) + 4 * sizeof(glm::mat4), sizeof(float), &nearPlane);
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4) + 4 * sizeof(glm::mat4) + sizeof(float), sizeof(float), &farPlane);


		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	skyboxMaterial->SetMat4("R_MAT", projectionMat * glm::mat4(glm::mat3(viewMat)));
	skyboxMaterial->Use();
	skyMesh->Draw();
}

void RCameraComponent::SetFieldOfView(const float& fov)
{
	fieldOfView = fov;
	CalculateProjectionMat();
}

void RCameraComponent::SetNearPlane(const float& near)
{
	nearPlane = near;
	CalculateProjectionMat();
}

void RCameraComponent::SetFarPlane(const float& far)
{
	farPlane = far;
	CalculateProjectionMat();
}

void RCameraComponent::CalculateProjectionMat()
{
	auto window = GetEntity().lock()->GetGame().GetGameWindow();
	float aspect = window.GetWidth() / window.GetHeight();
	projectionMat = glm::perspective(glm::radians(fieldOfView), aspect, nearPlane, farPlane);
}
