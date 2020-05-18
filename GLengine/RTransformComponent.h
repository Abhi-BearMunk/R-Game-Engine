#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Component.h"

class RTransformComponent :
	public RComponent
{
public:
	RTransformComponent(const std::weak_ptr<REntity> _entity, 
		const glm::vec3& _position = glm::vec3(0, 0, 0), 
		const glm::vec3& _scale = glm::vec3(1, 1, 1), 
		const glm::vec3& _eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));
	virtual void Start() override;
	virtual void Update() override;
	void SetPosition(const glm::vec3& _position);
	void SetScale(const glm::vec3& _scale);
	void SetRotation(const glm::vec3& _rotation);
	glm::quat RotationBetweenVectors(const glm::vec3& start, const glm::vec3& dest);
	void LookAt(const glm::vec3& point, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
	void Rotate(const float& angle, const glm::vec3& axis);
	inline const glm::vec3& GetPosition() { return position; }
	inline const glm::vec3& GetScale() { return scale; }
	inline const glm::quat& GetOrientation() { return orientation; }
	inline const glm::mat4& GetTransformationMatrix() { return transformationMatrix; }
	inline const glm::mat4& GetWorldToLocalMatrix() { return worldToLocalMatrix; }
	inline const glm::mat4& GetUnscaledTransformationMatrix() { return unscaledTransformationMatrix; }
	inline const glm::mat4& GetUnscaledWorldToLocalMatrix() { return unscaledWorldToLocalMatrix; }
	inline const glm::mat4& GetScaleMatrix() { return scaleMatrix; }
	inline const glm::mat4& GetRotationMatrix() { return rotationMatrix; }
	inline const glm::mat4& GetTranslationMatrix() { return translationMatrix; }
	inline glm::vec3 Up() { return orientation * glm::vec3(0.0f, 1.0f, 0.0f); }
	inline glm::vec3 Right() { return orientation * glm::vec3(1.0f, 0.0f, 0.0f);}
	inline glm::vec3 Forward() { return orientation * glm::vec3(0.0f, 0.0f, 1.0f); }
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat orientation;
	glm::mat4 scaleMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 translationMatrix;
	glm::mat4 unscaledTransformationMatrix;
	glm::mat4 transformationMatrix;
	glm::mat4 worldToLocalMatrix;
	glm::mat4 unscaledWorldToLocalMatrix;
	void UpdateMatrices();
	bool dirty = true;
};

