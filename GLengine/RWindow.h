#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class RTexture2D;
class RMaterial;
class RMesh;
class RFrameBuffer;
class RFrameBufferObject;
class RWindow
{
public:
	GLFWwindow* window;
	bool Init(const float& _width = 1920, const float& _height = 1080);
	void PreUpdate();
	void PostProcess();
	void FinishUpdate();
	void Blit(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest);
	void Blit(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest, std::weak_ptr<RMaterial> material, bool enableDepth = false, bool enableStencil = false);
	inline const float& GetWidth() { return width; }
	inline const float& GetHeight() { return height; }
	inline void SetGamma(float value);
	inline std::weak_ptr<RFrameBuffer> GetFrameBuffer() { return frameBuffer; }
	inline std::weak_ptr<RFrameBuffer> GetPostProcessFrameBuffer() { return postProcessframeBuffer; }
private:
	float width;
	float height;
	float gamma = 2.2f;
	std::shared_ptr<RFrameBuffer> frameBuffer;
	std::shared_ptr<RFrameBuffer> postProcessframeBuffer;
	std::shared_ptr<RMaterial> screenMat;
	std::shared_ptr<RMesh> screenQuad;
};

