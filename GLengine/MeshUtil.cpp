#include "MeshUtil.h"
#include "RMesh.h"

void MeshUtil::CreatePrimitive(PrimitiveType type, std::weak_ptr<RMesh> mesh)
{
	switch (type)
	{
	case MeshUtil::Quad:
		CreateQuad(mesh);
		break;
	case MeshUtil::Cube:
		CreateCube(mesh);
		break;
	case MeshUtil::Sphere:
		CreateSphere(mesh);
		break;
	case MeshUtil::ScreenQuad:
		CreateScreenQuad(mesh);
		break;
	}
}

void MeshUtil::CreateQuad(std::weak_ptr<RMesh> mesh)
{
	mesh.lock()->vertices = {
	Vertex(0.5, 0.5, 0, 0, 0, 1, 1, 1), //F0
	Vertex(0.5,-0.5, 0, 0, 0, 1, 1, 0), //F1
	Vertex(-0.5,-0.5, 0, 0, 0, 1, 0, 0), //F2
	Vertex(-0.5, 0.5, 0, 0, 0, 1, 0, 1), //F3
	};

	mesh.lock()->indices = {
		0, 1, 2,
		2, 3, 0,
	};

	// Finalize
	mesh.lock()->SetupMesh();
}

void MeshUtil::CreateCube(std::weak_ptr<RMesh> mesh)
{
	mesh.lock()->vertices = {
		Vertex( 0.5, 0.5, 0.5, 0, 0, 1, 1, 1), //F0
		Vertex( 0.5,-0.5, 0.5, 0, 0, 1, 1, 0), //F1
		Vertex(-0.5,-0.5, 0.5, 0, 0, 1, 0, 0), //F2
		Vertex(-0.5, 0.5, 0.5, 0, 0, 1, 0, 1), //F3
		Vertex( 0.5, 0.5,-0.5, 0, 1, 0, 1, 1), //T4
		Vertex( 0.5, 0.5, 0.5, 0, 1, 0, 1, 0), //T5
		Vertex(-0.5, 0.5, 0.5, 0, 1, 0, 0, 0), //T6
		Vertex(-0.5, 0.5,-0.5, 0, 1, 0, 0, 1), //T7
		Vertex( 0.5, 0.5,-0.5, 1, 0, 0, 1, 1), //R8
		Vertex( 0.5,-0.5,-0.5, 1, 0, 0, 1, 0), //R9
		Vertex( 0.5,-0.5, 0.5, 1, 0, 0, 0, 0), //R10
		Vertex( 0.5, 0.5, 0.5, 1, 0, 0, 0, 1), //R11
		Vertex(-0.5, 0.5,-0.5,-1, 0, 0, 1, 1), //L12
		Vertex(-0.5,-0.5,-0.5,-1, 0, 0, 1, 0), //L13
		Vertex(-0.5,-0.5, 0.5,-1, 0, 0, 0, 0), //L14
		Vertex(-0.5, 0.5, 0.5,-1, 0, 0, 0, 1), //L15
		Vertex( 0.5, 0.5,-0.5, 0, 0,-1, 1, 1), //B16
		Vertex( 0.5,-0.5,-0.5, 0, 0,-1, 1, 0), //B17
		Vertex(-0.5,-0.5,-0.5, 0, 0,-1, 0, 0), //B18
		Vertex(-0.5, 0.5,-0.5, 0, 0,-1, 0, 1), //B19
		Vertex( 0.5,-0.5,-0.5, 0,-1, 0, 1, 1), //D20
		Vertex( 0.5,-0.5, 0.5, 0,-1, 0, 1, 0), //D21
		Vertex(-0.5,-0.5, 0.5, 0,-1, 0, 0, 0), //D22
		Vertex(-0.5,-0.5,-0.5, 0,-1, 0, 0, 1), //D23

	};

	mesh.lock()->indices = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	// Finalize
	mesh.lock()->SetupMesh();
}

void MeshUtil::CreateSphere(std::weak_ptr<RMesh> mesh)
{
	float radius = 0.5f;
	float PI = 3.14159265359f;
	int sectorCount = 40;
	int stackCount = 16;

	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;

			mesh.lock()->vertices.push_back(Vertex(x, y, z, nx, ny, nz, s, t));

		}
	}

	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				mesh.lock()->indices.push_back(k1);
				mesh.lock()->indices.push_back(k2);
				mesh.lock()->indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stackCount - 1))
			{
				mesh.lock()->indices.push_back(k1 + 1);
				mesh.lock()->indices.push_back(k2);
				mesh.lock()->indices.push_back(k2 + 1);
			}
		}
	}

	// Finalize
	mesh.lock()->SetupMesh();
}

void MeshUtil::CreateScreenQuad(std::weak_ptr<RMesh> mesh)
{
	mesh.lock()->vertices = {
		Vertex( 1, 1, 0, 0, 0, 1, 1, 1), //F0
		Vertex( 1,-1, 0, 0, 0, 1, 1, 0), //F1
		Vertex(-1,-1, 0, 0, 0, 1, 0, 0), //F2
		Vertex(-1, 1, 0, 0, 0, 1, 0, 1), //F3
	};

	mesh.lock()->indices = {
		0, 1, 2,
		2, 3, 0,
	};

	// Finalize
	mesh.lock()->SetupMesh();
}
