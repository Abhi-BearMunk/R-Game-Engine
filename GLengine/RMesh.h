#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>

struct Vertex
{
	Vertex()
		:position(glm::vec3(0, 0, 0)), normal(glm::vec3(0, 0, 0)), texCoord(glm::vec2(0, 0))
	{
	}

	Vertex(const float& px, const float& py, const float& pz, const float& nx, const float& ny, const float& nz, const float& u, const float& v)
		:position(glm::vec3(px, py, pz)), normal(glm::vec3(nx, ny, nz)), texCoord(glm::vec2(u, v))
	{
	}
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class RMaterial;
class RRenderManager;
class RMesh
{
public:
	~RMesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::weak_ptr<RMaterial>> materials;
	void SetupMesh();
	void Draw();
	inline void Activate() { glBindVertexArray(VAO); }
	inline void Deactivate() { glBindVertexArray(0); }
private:
	unsigned int VAO, VBO, EBO;
};

