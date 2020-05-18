#pragma once
#include <memory>
#include <vector>
#include <algorithm>

class RGame;
class RComponent;
class REntity
{
public:
	REntity(RGame& _game);
	void Start();
	void Update();
	void Kill();
	template<typename T, class... Args> std::weak_ptr<T> AddComponent(Args&&... args);
	template<typename T> std::weak_ptr<T> GetComponent();
	template<typename T> void RemoveComponent();
	inline void SetSelf(std::weak_ptr<REntity> _self) { if (&*_self.lock() == this) self = _self; }
	inline const RGame& GetGame() const { return game; }
private:
	RGame& game;
	std::weak_ptr<REntity> self;
	// Only the Entity is the owner, 
	// ref count should never go above 1 (other that weakptr.lock), 
	// only interactions through weak ptrs
	std::vector<std::shared_ptr<RComponent>> components;
};

template<typename T, class... Args>
inline std::weak_ptr<T> REntity::AddComponent(Args&&... args)
{
	std::shared_ptr<T> component = std::make_shared<T>(self, args...);
	components.push_back(std::static_pointer_cast<RComponent>(component));
	return component;
}

template<class T>
inline std::weak_ptr<T> REntity::GetComponent()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		if (std::dynamic_pointer_cast<T>(*it))
		{
			return std::dynamic_pointer_cast<T>(*it);
		}
	}
	std::shared_ptr<T> empty;
	return empty;
}

template<typename T>
inline void REntity::RemoveComponent()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		if (static_cast<std::shared_ptr<T>>(*it))
		{
			components.erase(it);
		}
	}
}
