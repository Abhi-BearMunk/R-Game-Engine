#include <glm/glm.hpp>
#include "RModelComponent.h"
#include "Entity.h"
#include "RGame.h"
#include "RRenderManager.h"
#include "RMesh.h"
#include "Material.h"
#include "RCameraComponent.h"
#include "RTransformComponent.h"

RModelComponent::RModelComponent(const std::weak_ptr<REntity> _entity)
	:RComponent(_entity)
{
}

void RModelComponent::Start()
{
}

void RModelComponent::Update()
{
	if (!GetEntity().lock()->GetComponent<RTransformComponent>().expired())
	{
		auto transform = GetEntity().lock()->GetComponent<RTransformComponent>().lock();
		auto mainCamera = GetGame().mainCamera.lock();

		auto M = transform->GetTransformationMatrix();
		auto M_INV = transform->GetWorldToLocalMatrix();
		auto PV = mainCamera->GetViewProjectionMat();
		auto PV_INV = mainCamera->GetInvViewProjectionMat();

		auto MVP = PV * M;
		auto MVP_INV = M_INV * PV_INV;

		std::map<std::string, glm::mat4> data;
		data.insert({ "R_MATRIX_M", M });
		data.insert({ "R_MATRIX_MVP", MVP });
		data.insert({ "R_MATRIX_MVP_INV", MVP_INV });
		data.insert({ "R_MATRIX_NORMAL", glm::transpose(glm::inverse(M)) });

		// Draw meshes
		for (auto mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
		{
			for (auto mat = (*mesh)->materials.begin(); mat != (*mesh)->materials.end(); ++mat)
			{
				GetEntity().lock()->GetGame().GetRenderManager().lock()->QueueDrawCall(*mesh, *mat, data);
			}
		}
	}
}
