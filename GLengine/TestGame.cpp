#include "TestGame.h"
#include "Entity.h"
#include "RModelComponent.h"
#include "RMesh.h"
#include "Texture.h"
#include "MeshUtil.h"
#include "RColor.h"
#include "RPointLightComponent.h"
#include "RDirectionalLightComponent.h"
#include "RTransformComponent.h"
#include "RCameraComponent.h"
#include "RCubeMap.h"
#include "RMoveInCircle.h"
#include "RWindow.h"
#include "RFrameBuffer.h"

#define RANDOM(a,b) a + std::rand() * (b - a) / RAND_MAX

void TestGame::Setup()
{
	SetupMaterials();

	// Create Entities
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Sphere, {defaulSphereMat}, glm::vec3(0, 5, 0), glm::vec3(3, 3, 3), glm::vec3(50, -30, 0));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Cube, { boxOutline1Mat, Outline2Mat }, glm::vec3(0.5 * 3, -0.0, 3 * 3), glm::vec3(1.2, 1.2, 1.2), glm::vec3(15, 20, 70));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Cube, { boxOutline1Mat, Outline2Mat }, glm::vec3(-4 * 3, 0.1, -1 * 3));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Cube, { boxOutline1Mat, Outline2Mat }, glm::vec3(4 * 3, 0.2, 0));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Cube, { defaulBoxMat }, glm::vec3(-1.5 * 3, 1, -2 * 3));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Cube, { defaulBoxMat }, glm::vec3(-3 * 3, 0.4, 3 * 3));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Cube, { defaulBoxMat }, glm::vec3(2.5 * 3, 0.3, 2 * 3));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Cube, { defaulFloorMat }, glm::vec3(0, -1, 0), glm::vec3(30, 0.2, 30));

	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Quad, { transparentWindowMat }, glm::vec3(0, 1.5, 15), glm::vec3(30, 10, 5));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Quad, { transparentWindowMat }, glm::vec3(0, 1.5, -15), glm::vec3(30, 10, 5));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Quad, { transparentWindowMat }, glm::vec3(15, 1.5, 0), glm::vec3(30, 10, 5), glm::vec3(0, 90, 0));
	CreatePrimitiveEntity(MeshUtil::PrimitiveType::Quad, { transparentWindowMat }, glm::vec3(-15, 1.5, 0), glm::vec3(30, 10, 5), glm::vec3(0, 90, 0));

	for (int i = 0; i < 20; i++)
	{
		CreatePrimitiveEntity(MeshUtil::PrimitiveType::Quad, { grassMat }, glm::vec3(RANDOM(-4.0f, 4.0f), -0.5f, RANDOM(-4.0f, 4.0f)), glm::vec3(1, 1, 1), glm::vec3(0, RANDOM(-180.0F, 180.0f), 0));
	}

	// Lights
	auto pointLight1 = CreateEntity();
	pointLight1.lock()->AddComponent<RTransformComponent>(glm::vec3(0, 3, 5));
	pointLight1.lock()->AddComponent<RPointLightComponent>(RColor::Cyan, 10);
	pointLight1.lock()->AddComponent<RMoveInCircle>(30, 10, glm::vec3(0, 3, 0));

	auto pointLight2 = CreateEntity();
	pointLight2.lock()->AddComponent<RTransformComponent>(glm::vec3(-6, 2, 8));
	pointLight2.lock()->AddComponent<RPointLightComponent>(RColor::Purple, 10);

	auto pointLight3 = CreateEntity();
	pointLight3.lock()->AddComponent<RTransformComponent>(glm::vec3(8, 1, -6));
	pointLight3.lock()->AddComponent<RPointLightComponent>(RColor::Green, 10);

	/*auto pointLight4 = CreateEntity();
	pointLight4.lock()->AddComponent<RTransformComponent>(glm::vec3(0, 1, 0));
	pointLight4.lock()->AddComponent<RPointLightComponent>(RColor::Red, 500);*/

	auto dirLight1 = CreateEntity();
	dirLight1.lock()->AddComponent<RTransformComponent>(glm::vec3(0, 0, 5), glm::vec3(1, 1, 1), glm::vec3(135, 0, 0));
	dirLight1.lock()->AddComponent<RDirectionalLightComponent>(RColor::FromVec4(RColor::Beige * 1.0f));
}

void TestGame::PostProcess(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest)
{
	std::shared_ptr<RFrameBuffer> temp1 = std::make_shared<RFrameBuffer>(GetGameWindow().GetWidth(), GetGameWindow().GetHeight(), ImageFormat::RGB, FrameBufferObjectType::R_NONE);
	std::shared_ptr<RFrameBuffer> temp2 = std::make_shared<RFrameBuffer>(GetGameWindow().GetWidth(), GetGameWindow().GetHeight(), ImageFormat::RGB, FrameBufferObjectType::R_NONE);

	GetGameWindow().Blit(src, temp1, PostProcessMat, false, true);

	GetGameWindow().Blit(src, temp2, PostProcessMat2, false, true);
	PostProcessMat3->SetTexture("Source_Texture2", temp2->GetColorBufferTexture().lock());

	GetGameWindow().Blit(temp1, dest, PostProcessMat3);
}

void TestGame::SetupMaterials()
{
	// Textures
	auto boxTexDiff = std::make_shared<RTexture2D>("Assets/ContainerDiff.png", true, WrapMode::Repeat);
	auto boxTexSpec = std::make_shared<RTexture2D>("Assets/ContainerSpec.png", false, WrapMode::Repeat);
	auto floorTexDiff = std::make_shared<RTexture2D>("Assets/HexagonTile_DIFF.png", true, WrapMode::Repeat);
	auto floorTexSpec = std::make_shared<RTexture2D>("Assets/HexagonTile_SPEC.png", false, WrapMode::Repeat);
	auto sphereTexDiff = std::make_shared<RTexture2D>("Assets/marble/marble_0013_base_color_2k.jpg", true, WrapMode::Repeat);
	auto grassTexDiff = std::make_shared<RTexture2D>("Assets/grass.png", true, WrapMode::Repeat);
	auto windowTexDiff = std::make_shared<RTexture2D>("Assets/blending_transparent_window.png", true, WrapMode::Repeat);

	//auto sphereTexSpec = std::make_shared<RTexture>("Assets/marble/marble_0013_roughness_2k.jpg", WrapMode::Repeat);

	// Default Box Material
	defaulBoxMat = std::make_shared<RMaterial>("Shaders/SimpleVertex.vs", "Shaders/SimpleFrag.fs");
	defaulBoxMat->SetTexture("Texture_Diffuse", boxTexDiff);
	defaulBoxMat->SetTexture("Texture_Specular", boxTexSpec);
	defaulBoxMat->SetVec2("tiling", glm::vec2(1, 1));
	defaulBoxMat->SetFloat("shininess", 8);

	// Default Sphere Material
	defaulSphereMat = std::make_shared<RMaterial>("Shaders/MovingTrianglesVert.vs", "Shaders/MovingTrianglesFrag.fs", "Shaders/MovingTrianglesGeom.gs");
	defaulSphereMat->cull = false;
	defaulSphereMat->SetTexture("Texture_Diffuse", sphereTexDiff);
	defaulSphereMat->SetTexture("Texture_Reflection", mainCamera.lock()->defaultSkybox);
	//defaulSphereMat->SetTexture("Texture_Specular", sphereTexSpec);
	defaulSphereMat->SetVec2("tiling", glm::vec2(1, 1));
	defaulSphereMat->SetFloat("shininess", 128);

	// Default Floor Material
	defaulFloorMat = std::make_shared<RMaterial>("Shaders/SimpleVertex.vs", "Shaders/SimpleFrag.fs");
	defaulFloorMat->SetTexture("Texture_Diffuse", floorTexDiff);
	defaulFloorMat->SetTexture("Texture_Specular", floorTexSpec);
	defaulFloorMat->SetVec2("tiling", glm::vec2(10, 10));
	defaulFloorMat->SetFloat("shininess", 32);

	// Default Grass Material
	grassMat = std::make_shared<RMaterial>("Shaders/SimpleVertex.vs", "Shaders/AlphaDiscard.fs");
	grassMat->cull = false;
	grassMat->SetTexture("Texture_Diffuse", grassTexDiff);
	grassMat->SetVec2("tiling", glm::vec2(1, 1));
	grassMat->SetFloat("shininess", 128);

	// Transparent Window Material
	transparentWindowMat = std::make_shared<RMaterial>("Shaders/SimpleVertex.vs", "Shaders/SimpleFrag.fs");
	transparentWindowMat->renderQueue = 4000;
	transparentWindowMat->cull = false;
	transparentWindowMat->alpha = true;
	transparentWindowMat->depthMask = GL_FALSE;
	transparentWindowMat->SetTexture("Texture_Diffuse", windowTexDiff);
	transparentWindowMat->SetVec2("tiling", glm::vec2(1, 1));
	transparentWindowMat->SetFloat("shininess", 128);

	// Box Outline stencil write Material 
	boxOutline1Mat = std::make_shared<RMaterial>("Shaders/SimpleVertex.vs", "Shaders/SimpleFrag.fs");
	boxOutline1Mat->stencilFunc = GL_ALWAYS;
	boxOutline1Mat->stencilRef = 1;
	boxOutline1Mat->stencilPassDepthFail = GL_REPLACE;
	boxOutline1Mat->stencilDepthPass = GL_REPLACE;
	boxOutline1Mat->SetTexture("Texture_Diffuse", boxTexDiff);
	boxOutline1Mat->SetTexture("Texture_Specular", boxTexSpec);
	boxOutline1Mat->SetVec2("tiling", glm::vec2(1, 1));
	boxOutline1Mat->SetFloat("shininess", 128);

	// Extruded Outline stencil read Material 
	Outline2Mat = std::make_shared<RMaterial>("Shaders/OutlineVert.vs", "Shaders/OutlineFrag.fs");
	Outline2Mat->renderQueue = 2002;
	Outline2Mat->stencilFunc = GL_NOTEQUAL;
	Outline2Mat->stencilRef = 1;
	Outline2Mat->depthFunc = GL_ALWAYS;
	Outline2Mat->SetFloat("extrudeLength", 0.05f);
	Outline2Mat->SetVec4("outlineColor", RColor::Cyan);

	// Post Process Materials
	PostProcessMat = std::make_shared<RMaterial>("Shaders/ScreenVertex.vs", "Shaders/PostProcessTest.fs");
	PostProcessMat->stencilFunc = GL_EQUAL;
	PostProcessMat->stencilRef = 1;
	//PostProcessMat->depthFunc = GL_ALWAYS;

	PostProcessMat2 = std::make_shared<RMaterial>("Shaders/ScreenVertex.vs", "Shaders/ScreenFrag.fs");
	PostProcessMat2->stencilFunc = GL_NOTEQUAL;
	PostProcessMat2->stencilRef = 1;

	PostProcessMat3 = std::make_shared<RMaterial>("Shaders/ScreenVertex.vs", "Shaders/PostCombine.fs");
}

std::weak_ptr<REntity> TestGame::CreatePrimitiveEntity(MeshUtil::PrimitiveType type, const std::vector<std::weak_ptr<RMaterial>>& materials, const glm::vec3& _position, const glm::vec3& _scale, const glm::vec3& _eulerAngles)
{

	// Create entity and add transform
	auto entity = CreateEntity();
	entity.lock()->AddComponent<RTransformComponent>(_position, _scale, _eulerAngles);

	// Create and setup mesh
	std::shared_ptr<RMesh> mesh = std::make_shared<RMesh>();
	MeshUtil::CreatePrimitive(type, mesh);
	mesh->materials = materials;

	// Create model component and add mesh and material
	auto boxModel = entity.lock()->AddComponent<RModelComponent>();
	boxModel.lock()->meshes.push_back(mesh);

	return entity;
}
