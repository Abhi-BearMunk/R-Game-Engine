#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class REntity;
class RMesh;
class RMaterial;
class RCubeMap;
class RCameraComponent :
	public RComponent
{
public:
	RCameraComponent(const std::weak_ptr<REntity> _entity, const float& fov = 60, const float& near = 0.01f, const float& far = 1000.0f);
	
	void Start();
	void Update();

	void SetFieldOfView(const float& fov);
	void SetNearPlane(const float& near);
	void SetFarPlane(const float& far);

	inline const float& GetFieldOfView() const { return fieldOfView; }
	inline const float& GetNearPlane() const { return nearPlane; }
	inline const float& GetFarPlane() const { return farPlane; }
	inline const glm::mat4& GetProjectionMat() const { return projectionMat; }
	inline const glm::mat4& GetViewMat() const { return viewMat; }
	inline const glm::mat4& GetViewProjectionMat() const { return viewProjectionMat; }
	inline const glm::mat4& GetInvViewProjectionMat() const { return invViewProjectionMat; }

	std::shared_ptr<RCubeMap> defaultSkybox;
	std::shared_ptr<RMaterial> skyboxMaterial;
private:
	float fieldOfView;
	float nearPlane;
	float farPlane;
	std::shared_ptr<RMesh> skyMesh;

	glm::mat4 projectionMat;
	glm::mat4 viewMat;
	glm::mat4 viewProjectionMat;
	glm::mat4 invViewProjectionMat;

	void CalculateProjectionMat();

	unsigned int cameraUBO;
};

