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

		// Draw meshes
		for (auto mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
		{
			for (auto mat = (*mesh)->materials.begin(); mat != (*mesh)->materials.end(); ++mat)
			{
				GetEntity().lock()->GetGame().GetRenderManager().lock()->QueueDrawCall(*mesh, *mat, transform);
			}
		}
	}
}
