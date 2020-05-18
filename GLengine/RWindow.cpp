#include "RWindow.h"
#include "Texture.h"
#include "Material.h"
#include "RMesh.h"
#include "MeshUtil.h"
#include "RFrameBuffer.h"
#include "RFrameBufferObject.h"

bool RWindow::Init(const float& _width, const float& _height)
{
	width = _width;
	height = _height;

	// Initialize OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window, handle errors
	window = glfwCreateWindow(width, height, "GLEngine", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR : Window not created" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Load Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// Create the Viewport
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, [](auto window, int width, int height) {glViewport(0, 0, width, height); });

	// Enable depth and stencil
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	// Create FrameBuffer
	frameBuffer = std::make_shared<RFrameBuffer>(width, height);
	postProcessframeBuffer = std::make_shared<RFrameBuffer>(width, height, ImageFormat::RGB, FrameBufferObjectType::R_NONE);

	if (!frameBuffer->IsComplete() || !postProcessframeBuffer->IsComplete())
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		return false;
	}

	RFrameBuffer::SetDefault();

	// Create Screen Quad and Material
	screenMat = std::make_shared<RMaterial>("Shaders/ScreenVertex.vs", "Shaders/ScreenFrag.fs");
	screenQuad = std::make_shared<RMesh>();
	MeshUtil::CreatePrimitive(MeshUtil::PrimitiveType::ScreenQuad, screenQuad);
	//screenQuad->materials.push_back(screenMat);

	// Disable cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

void RWindow::PreUpdate()
{
	frameBuffer->Activate();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
}

void RWindow::PostProcess()
{
	RFrameBuffer::SetDefault(); // back to default
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);

	screenMat->SetTexture("Source_Texture", postProcessframeBuffer->GetColorBufferTexture().lock());
	screenMat->Use();
	screenQuad->Draw();
}

void RWindow::FinishUpdate()
{
	// Check events and swap buffer
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void RWindow::Blit(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest)
{
	Blit(src, dest, screenMat);
}

void RWindow::Blit(std::weak_ptr<RFrameBuffer> src, std::weak_ptr<RFrameBuffer> dest, std::weak_ptr<RMaterial> material, bool enableDepth, bool enableStencil)
{
	dest.lock()->Activate();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!src.lock()->GetDepthStencilBuffer().expired())
	{
		dest.lock()->SetDepthBuffer(src.lock()->GetDepthStencilBuffer().lock());
	}
	enableDepth ? glEnable(GL_DEPTH) : glDisable(GL_DEPTH);
	enableStencil ? glEnable(GL_STENCIL) : glDisable(GL_STENCIL);
	material.lock()->SetTexture("Source_Texture", src.lock()->GetColorBufferTexture().lock());
	material.lock()->Use();
	screenQuad->Draw();
}

