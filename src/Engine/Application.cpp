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
	{
		assert(("Ensure only one application instance is valid at a time", App == nullptr));

		SetupWindowing();
		mWindow = CreateWindow(title, width, height);

		SetupEvents();

		App = this;
	}


	void TApp::SetupWindowing()
	{
		assert(("Failed to initialize GLFW", glfwInit() == GLFW_TRUE));

		glfwWindowHint(GLFW_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	}


	void TApp::SetupEvents()
	{
		OnUpdateListener = OnUpdate.Connect([this](float dt) {
			Update(dt);
		});
	}


	GLFWwindow* TApp::CreateWindow(const char* title, unsigned int width, unsigned int height)
	{
		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(window);

		glewInit();

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

		glClear(GL_COLOR_BUFFER_BIT);
		
		float deltaTime = frameTimer.GetElapsed();
		frameTimer.Restart();

		OnUpdate.Dispatch(deltaTime);
	
		glfwSwapBuffers(mWindow);
	}


	void TApp::Update(float deltaTime)
	{

	}
}