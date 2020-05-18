#include <algorithm>    
#include "RRenderManager.h"
#include "RGame.h"
#include "RMesh.h"
#include "Material.h"
#include "RTransformComponent.h"
#include "RCameraComponent.h"

RRenderManager::RRenderManager(RGame& _game)
	:game(_game)
{
}

void RRenderManager::QueueDrawCall(std::weak_ptr<RMesh> mesh, std::weak_ptr<RMaterial> material, std::weak_ptr<RTransformComponent> transform)
{
	if (drawCallQueue.size() == 0)
	{
		drawCallQueue.push_back(std::make_tuple(mesh, material, transform));
		return;
	}
	else if (std::get<1>(drawCallQueue[drawCallQueue.size() - 1]).lock()->renderQueue <= material.lock()->renderQueue)
	{
		drawCallQueue.push_back(std::make_tuple(mesh, material, transform));
		return;
	}
	else if (std::get<1>(drawCallQueue[0]).lock()->renderQueue >= material.lock()->renderQueue)
	{
		drawCallQueue.insert(drawCallQueue.begin(), std::make_tuple(mesh, material, transform));
		return;
	}
	
	unsigned int queue = material.lock()->renderQueue;
	unsigned int start = 0;
	unsigned int end = drawCallQueue.size() - 1;

	while (end - start > 1)
	{
		if (std::get<1>(drawCallQueue[start]).lock()->renderQueue == material.lock()->renderQueue)
		{
			drawCallQueue.insert(drawCallQueue.begin() + start, std::make_tuple(mesh, material, transform));
			return;
		}
		else if(std::get<1>(drawCallQueue[start]).lock()->renderQueue == material.lock()->renderQueue)
		{
			drawCallQueue.insert(drawCallQueue.begin() + end, std::make_tuple(mesh, material, transform));
			return;
		}
		unsigned int newIndex = floor((start + end) / 2);
		if (std::get<1>(drawCallQueue[newIndex]).lock()->renderQueue >= material.lock()->renderQueue)
		{
			end = newIndex;
			continue;
		}
		else 
		{
			start = newIndex;
			continue;
		}
	}

	drawCallQueue.insert(drawCallQueue.begin() + start + 1, std::make_tuple(mesh, material, transform));
}

void RRenderManager::Update()
{
	for (size_t i = 0; i < drawCallQueue.size(); i++)
	{
		auto mesh = std::get<0>(drawCallQueue[i]).lock();
		auto material = std::get<1>(drawCallQueue[i]).lock();
		auto transform = std::get<2>(drawCallQueue[i]).lock();
		auto mainCamera = game.mainCamera.lock();

		auto M = transform->GetTransformationMatrix();
		auto M_INV = transform->GetWorldToLocalMatrix();
		auto PV = mainCamera->GetViewProjectionMat();
		auto PV_INV = mainCamera->GetInvViewProjectionMat();

		auto MVP = PV * M;
		auto MVP_INV = M_INV * PV_INV;

		if (material->alpha)
		{
			glEnable(GL_BLEND);
		}

		material->SetMat4("R_MATRIX_M", M);
		material->SetMat4("R_MATRIX_MVP", MVP);
		material->SetMat4("R_MATRIX_MVP_INV", MVP_INV);
		material->SetMat4("R_MATRIX_NORMAL", glm::transpose(glm::inverse(M)));
		material->Use();

		mesh->Draw();

		glDisable(GL_BLEND);
	}

	drawCallQueue.clear();
}
