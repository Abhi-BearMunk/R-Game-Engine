#pragma once
#include <memory>
#include <list>
#include <vector>
#include <algorithm>
#include <glm/glm.hpp>
//#include "Material.h"

class RWindow;
class RCameraComponent;
class RLightingManager;
class RRenderManager;
class RShaderUtilsManager;
class REntity;
class RFrameBuffer;
class RGame
{
private:
	RWindow* gameWindow = nullptr;
	const std::shared_ptr<RLightingManager> lightingManager;
	const std::shared_ptr<RRenderManager> renderManager;
	const std::shared_ptr<RShaderUtilsManager> shaderUtilsManager;

	bool isRunning = true;
	void ProcessGlobalInputs();

	std::list<std::shared_ptr<REntity>> entities;
	std::list<std::weak_ptr<REntity>> dyingEntities;
	void KillDyingEntities();
public:
	RGame();
	// Game loop
	bool Init();
	void Update();
	void Quit();
	const bool& GetIsRunning() const;

	// EC
	std::weak_ptr<REntity> CreateEntity();
	void KillEntity(std::weak_ptr<REntity> entity);

	// Rendering
	inline RWindow& GetGameWindow() const { return *gameWindow; }
	std::weak_ptr<RCameraComponent> mainCamera;

	inline std::weak_ptr<RLightingManager> GetLightingManager() const { return lightingManager; }
	inline std::weak_ptr<RRenderManager> GetRenderManager() const { return renderManager; }

protected:
	virtual void Setup() = 0;
	virtual void PostProcess(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest);
};

