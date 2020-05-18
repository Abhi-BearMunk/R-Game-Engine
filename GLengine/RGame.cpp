#include <algorithm>
#include "RGame.h"
#include "RWindow.h"
#include "Entity.h"
#include "RLightingManager.h"
#include "RRenderManager.h"
#include "RCameraComponent.h"
#include "RTransformComponent.h"
#include "RFPSMoveComponent.h"
#include "RFrameBuffer.h"

RGame::RGame()
	:lightingManager(std::make_shared<RLightingManager>()),
	renderManager(std::make_shared<RRenderManager>(*this))
{
}

std::weak_ptr<REntity> RGame::CreateEntity()
{
	auto entity = std::make_shared<REntity>(*this);
	entity->SetSelf(entity);
	entities.push_back(entity);
	return entity;
}

void RGame::KillEntity(std::weak_ptr<REntity> entity)
{
	dyingEntities.push_back(entity);
}

void RGame::PostProcess(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest)
{
	gameWindow->Blit(src, dest);
}

void RGame::KillDyingEntities()
{
	std::for_each(dyingEntities.begin(), dyingEntities.end(),
		[this](std::weak_ptr<REntity> entity) {
			entities.remove(entity.lock());
		});
	dyingEntities.clear();
}

bool RGame::Init()
{
	// Create Window
	gameWindow = new RWindow();
	if (!gameWindow->Init())
	{
		return false;
	}

	// Init Managers
	lightingManager->Init();

	// Create Camera
	auto camera = CreateEntity();
	camera.lock()->AddComponent<RTransformComponent>(glm::vec3(0, 5, 10));
	camera.lock()->AddComponent<RFPSMoveComponent>();
	mainCamera = camera.lock()->AddComponent<RCameraComponent>();


	// Create entities etc.
	Setup();

	// Start Entities;
	std::for_each(entities.begin(), entities.end(),
		[](const auto& entity) {entity->Start(); });

	return true;
}

void RGame::Update()
{
	// Rendering
	gameWindow->PreUpdate();

	// GamePlay
	ProcessGlobalInputs();
	std::for_each(entities.begin(), entities.end(),
		[](const auto& entity) {entity->Update(); });

	// Finish update
	lightingManager->Update();
	renderManager->Update();

	PostProcess(gameWindow->GetFrameBuffer(), gameWindow->GetPostProcessFrameBuffer());

	gameWindow->PostProcess();
	gameWindow->FinishUpdate();
	KillDyingEntities();
	isRunning = !glfwWindowShouldClose(gameWindow->window);
}

void RGame::Quit()
{
	glfwSetWindowShouldClose(gameWindow->window, true);
}

const bool& RGame::GetIsRunning() const
{
	return isRunning;
}


void RGame::ProcessGlobalInputs()
{
	if (glfwGetKey(gameWindow->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		Quit();
	}
}
