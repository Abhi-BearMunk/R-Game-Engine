#pragma once
#include <memory>
#include "RGame.h"
#include "Material.h"
#include "MeshUtil.h"

class TestGame :
	public RGame
{
protected:
	virtual void Setup() override;
	virtual void PostProcess(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest) override;
	std::shared_ptr<RMaterial> defaulBoxMat;
	std::shared_ptr<RMaterial> defaulSphereMat;
	std::shared_ptr<RMaterial> defaulFloorMat;
	std::shared_ptr<RMaterial> grassMat;
	std::shared_ptr<RMaterial> transparentWindowMat;
	std::shared_ptr<RMaterial> boxOutline1Mat;
	std::shared_ptr<RMaterial> Outline2Mat;
	std::shared_ptr<RMaterial> PostProcessMat;
	std::shared_ptr<RMaterial> PostProcessMat2;
	std::shared_ptr<RMaterial> PostProcessMat3;

	void SetupMaterials();
	// Utils
	std::weak_ptr<REntity> CreatePrimitiveEntity(
		MeshUtil::PrimitiveType type, 
		const std::vector<std::weak_ptr<RMaterial>>& materials, 
		const glm::vec3& _position = glm::vec3(0, 0, 0),
		const glm::vec3& _scale = glm::vec3(1, 1, 1),
		const glm::vec3& _eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f));
};

