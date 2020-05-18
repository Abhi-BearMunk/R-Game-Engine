#pragma once
#include <memory>

class REntity;
class RGame;
class RComponent
{
public:
	RComponent(const std::weak_ptr<REntity> _entity);
	virtual ~RComponent();
	virtual void Start() = 0;
	virtual void Update() = 0;
	inline const std::weak_ptr<REntity> GetEntity() { return entity; }
	const RGame& GetGame() const;
private:
	const std::weak_ptr<REntity> entity;
};

