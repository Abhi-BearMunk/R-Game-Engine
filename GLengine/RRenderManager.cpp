#include <algorithm>    
#include "RRenderManager.h"
#include "RMesh.h"
#include "Material.h"

RRenderManager::RRenderManager(RGame& _game)
	:game(_game)
{
}

void RRenderManager::QueueDrawCall(std::weak_ptr<RMesh> mesh, std::weak_ptr<RMaterial> material, std::map<std::string, glm::mat4> data)
{
	if (drawCallQueue.size() == 0)
	{
		drawCallQueue.push_back(std::make_tuple(mesh, material, data));
		return;
	}
	else if (std::get<1>(drawCallQueue[drawCallQueue.size() - 1]).lock()->renderQueue <= material.lock()->renderQueue)
	{
		drawCallQueue.push_back(std::make_tuple(mesh, material, data));
		return;
	}
	else if (std::get<1>(drawCallQueue[0]).lock()->renderQueue >= material.lock()->renderQueue)
	{
		drawCallQueue.insert(drawCallQueue.begin(), std::make_tuple(mesh, material, data));
		return;
	}
	
	unsigned int queue = material.lock()->renderQueue;
	unsigned int start = 0;
	unsigned int end = drawCallQueue.size() - 1;

	while (end - start > 1)
	{
		if (std::get<1>(drawCallQueue[start]).lock()->renderQueue == material.lock()->renderQueue)
		{
			drawCallQueue.insert(drawCallQueue.begin() + start, std::make_tuple(mesh, material, data));
			return;
		}
		else if(std::get<1>(drawCallQueue[start]).lock()->renderQueue == material.lock()->renderQueue)
		{
			drawCallQueue.insert(drawCallQueue.begin() + end, std::make_tuple(mesh, material, data));
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

	drawCallQueue.insert(drawCallQueue.begin() + start + 1, std::make_tuple(mesh, material, data));
}

void RRenderManager::Update()
{
	for (size_t i = 0; i < drawCallQueue.size(); i++)
	{
		auto mesh = std::get<0>(drawCallQueue[i]).lock();
		auto material = std::get<1>(drawCallQueue[i]).lock();
		auto data = std::get<2>(drawCallQueue[i]);

		material->cull ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
		material->alpha ? glEnable(GL_BLEND) : glDisable(GL_BLEND);

		for (auto it = data.begin(); it != data.end(); ++it)
		{
			material->SetMat4(it->first, it->second);
		}
		material->Use();
		mesh->Draw();
	}
	drawCallQueue.clear();
}
