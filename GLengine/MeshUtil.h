#pragma once
#include <memory>

class RMesh;
class MeshUtil
{

public:
	enum PrimitiveType
	{
		Quad,
		Cube,
		Sphere,
		ScreenQuad
	};
	static void CreatePrimitive(PrimitiveType type, std::weak_ptr<RMesh> mesh);
private:
	static void CreateQuad(std::weak_ptr<RMesh> mesh);
	static void CreateCube(std::weak_ptr<RMesh> mesh);
	static void CreateSphere(std::weak_ptr<RMesh> mesh);
	static void CreateScreenQuad(std::weak_ptr<RMesh> mesh);
};

