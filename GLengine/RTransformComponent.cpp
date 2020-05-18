#define DEG_TO_RAD 0.0174533f
#include <iostream>
#include "RTransformComponent.h"

RTransformComponent::RTransformComponent(const std::weak_ptr<REntity> _entity,
	const glm::vec3& _position, const glm::vec3& _scale, const glm::vec3& _eulerAngles)
	:RComponent(_entity),
	position(_position), 
	scale(_scale), 
	orientation(glm::quat(DEG_TO_RAD * _eulerAngles)),
	dirty(true)
{
	UpdateMatrices();
}

void RTransformComponent::Start()
{
}

void RTransformComponent::Update()
{
}

void RTransformComponent::SetPosition(const glm::vec3& _position)
{
	position = _position;
	UpdateMatrices();
}

void RTransformComponent::SetScale(const glm::vec3& _scale)
{
	scale = _scale;
	UpdateMatrices();
}

void RTransformComponent::SetRotation(const glm::vec3& _eulerAngles)
{
	orientation = glm::quat(DEG_TO_RAD * _eulerAngles);
	UpdateMatrices();
}

glm::quat RTransformComponent::RotationBetweenVectors(const glm::vec3& from, const glm::vec3& to)
{
	if (glm::length2(from) == 0.0f || glm::length2(to) == 0.0f)
	{
		return glm::quat(1, 0, 0, 0);
	}
	auto start = glm::normalize(from);
	auto dest = glm::normalize(to);

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f) {
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = glm::cross(start, dest);

	// 2 cos theta by 2
	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		// rotation axis divided 2 * cos theta by 2 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);
}

void RTransformComponent::LookAt(const glm::vec3& point, const glm::vec3& up)
{
	glm::vec3 toVector = point - position;
	if (glm::length2(toVector) == 0.0f)
	{
		std::cout << "Failed to look at NAN direction" << std::endl;
		return;
	}
	glm::quat rot1 = RotationBetweenVectors(Forward(), toVector);

	glm::vec3 right = glm::cross(toVector, up);
	glm::vec3 desiredUp = glm::cross(right, toVector);

	// Because of the 1rst rotation, the up is probably completely screwed up.
	// Find the rotation between the "up" of the rotated object, and the desired up
	glm::vec3 newUp = rot1 * Up();
	glm::quat rot2 = RotationBetweenVectors(newUp, desiredUp);

	orientation = rot2 * rot1 * orientation;
	UpdateMatrices();
}

void RTransformComponent::Rotate(const float& angle, const glm::vec3& axis)
{
	orientation = glm::angleAxis(angle, axis) * orientation;
	UpdateMatrices();
}

void RTransformComponent::UpdateMatrices()
{
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	rotationMatrix = glm::toMat4(orientation);
	translationMatrix = glm::translate(glm::mat4(1.0f), position);
	unscaledTransformationMatrix = translationMatrix * rotationMatrix;
	unscaledWorldToLocalMatrix = glm::inverse(unscaledTransformationMatrix);
	transformationMatrix = unscaledTransformationMatrix * scaleMatrix;
	worldToLocalMatrix = glm::inverse(scaleMatrix) * unscaledWorldToLocalMatrix;
}
