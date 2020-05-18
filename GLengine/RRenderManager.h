#pragma once
#include <memory>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <glm/glm.hpp>

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
	void QueueDrawCall(std::weak_ptr<RMesh> mesh, std::weak_ptr<RMaterial> material, std::map<std::string, glm::mat4> data);
	void Update();
private:
	RGame& game;
	std::vector < std::tuple< std::weak_ptr<RMesh>, std::weak_ptr<RMaterial>, std::map<std::string, glm::mat4>>> drawCallQueue;
};

