#pragma once
#include <memory>
#include <vector>
#include <tuple>

class RGame;
class RMesh;
class RMaterial;
class RTransformComponent;
class RRenderManager
{
public:	
	RRenderManager(RGame& _game);
	/**
	Inserts draw call in queue by binary partition, sorted by render queue
	*/
	void QueueDrawCall(std::weak_ptr<RMesh> mesh, std::weak_ptr<RMaterial> material, std::weak_ptr<RTransformComponent> transform);
	void Update();
private:
	RGame& game;
	std::vector < std::tuple< std::weak_ptr<RMesh>, std::weak_ptr<RMaterial>, std::weak_ptr<RTransformComponent>>> drawCallQueue;

	//std::vector<std::pair<RMesh&, std::weak_ptr<RMaterial>>> materialsQueue;
};

