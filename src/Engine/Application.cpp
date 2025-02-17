#include "Engine/Application.h"

#include <cassert>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Engine/Stopwatch.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	TApp* GApp = nullptr;


	TApp::TApp(const char* title, unsigned int width, unsigned int height)
		: WindowWidth(width), WindowHeight(height)
	{
		assert(("Ensure only one application instance is valid at a time", GApp == nullptr));

		SetupWindowing();
		mWindow = CreateWindow(title, width, height);
		Input = new TInput(mWindow);

		SetupEvents();

		GApp = this;
	}


	TApp::~TApp()
	{
	}


	void TApp::SetupWindowing()
	{
		assert(("Failed to initialize GLFW", glfwInit() == GLFW_TRUE));

		glfwWindowHint(GLFW_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_SAMPLES, 4);
	}


	void TApp::SetupEvents()
	{
	}


	GLFWwindow* TApp::CreateWindow(const char* title, unsigned int width, unsigned int height)
	{
		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);

		return window;
	}


	void TApp::Start()
	{
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

		if (CurrentScene)
		{
			CurrentScene->OnUpdate.Dispatch(deltaTime);
			CurrentScene->Renderer.Render();
		}
	
		glfwSwapBuffers(mWindow);
	}


	void TApp::Update(float deltaTime)
	{

	}


    void TApp::Render()
    {

    }
}