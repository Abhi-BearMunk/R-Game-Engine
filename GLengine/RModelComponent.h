#pragma once
#include <vector>
#include <memory>
#include "Component.h"

class REntity;
class RMesh;
class RMaterial;
class RModelComponent :
	public RComponent
{
public:
	RModelComponent(const std::weak_ptr<REntity> _entity);
	virtual void Start() override;
	virtual void Update() override;
	std::vector<std::shared_ptr<RMesh>> meshes;
};

