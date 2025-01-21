#include "Engine/Application.h"

#include <cassert>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Engine/Stopwatch.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	TApp* App = nullptr;


	TApp::TApp(const char* title, unsigned int width, unsigned int height)
		: WindowWidth(width), WindowHeight(height)
	{
		assert(("Ensure only one application instance is valid at a time", App == nullptr));

		SetupWindowing();
		mWindow = CreateWindow(title, width, height);
		Input = new TInput(mWindow);

		Renderer.Setup();

		SetupEvents();

		App = this;
	}


	TApp::~TApp()
	{
		delete CurrentCamera;
	}


	void TApp::SetupWindowing()
	{
		assert(("Failed to initialize GLFW", glfwInit() == GLFW_TRUE));

		glfwWindowHint(GLFW_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_VERSION_MINOR, 2);
	}


	void TApp::SetupEvents()
	{
		OnUpdateListener = OnUpdate.Connect(std::bind_front(&TApp::Update, this));
		OnRenderListener = Renderer.OnRender.Connect(std::bind_front(&TApp::Render, this));
		Input->OnUpdateListener = OnUpdate.Connect(std::bind_front(&TInput::Update, Input));
	}


	GLFWwindow* TApp::CreateWindow(const char* title, unsigned int width, unsigned int height)
	{
		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);

		return window;
	}


	void TApp::Start()
	{
		CurrentCamera = new TCamera;

		while (!ShouldClose())
		{
			Tick();
		}
	}


	void TApp::Tick()
	{
		static TStopwatch frameTimer;

		glfwPollEvents();

		// Dispatch update
		float deltaTime = frameTimer.GetElapsed();
		frameTimer.Restart();

		OnUpdate.Dispatch(deltaTime);

		// Begin drawing
		Renderer.Render();
	
		glfwSwapBuffers(mWindow);
	}


	void TApp::Update(float deltaTime)
	{

	}


    void TApp::Render()
    {

    }
}