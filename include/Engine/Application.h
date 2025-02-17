#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "Core.h"
#include "Engine/Event.h"
#include "Engine/Notify.h"
#include "Engine/Scene.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Graphics/Renderer.h"


struct GLFWwindow;


namespace SYCAMORE_NAMESPACE
{
	/**
	 * @brief The root class of a Sycamore application.
	 */
	class TApp
	{
	public:
		/**
		 * @brief Sycamore's entry point
		 * @param title The title of the app window
		 * @param width 
		 * @param height 
		 */
		TApp(const char* title, unsigned int width, unsigned int height);
		~TApp();

		/**
		 * @brief Called immediately after the engine has initialized.
		 */
		virtual void Start();

		/**
		 * @brief Runs the core game loop.
		 */
		virtual void Tick();

		/**
		 * @brief Runs prior to rendering and physics, per-frame code should be used here.
		 * @param deltaTime 
		 */
		virtual void Update(float deltaTime);

		/**
		 * @brief Called while rendering, draw calls may be made here.
		 */
		virtual void Render();

		template<typename T>
		void UseScene()
		{
			std::cout << "Hello, world!" << std::endl;
			T* newScene = new T;

			CurrentScene = newScene;

			if (!CurrentScene->UsedBefore)
			{
				Input->OnUpdateListener = CurrentScene->OnUpdate.Connect(std::bind_front(&TInput::Update, Input));

				CurrentScene->Renderer.Setup();
				CurrentScene->BeginPlay();
				CurrentScene->UsedBefore = true;
			}
		}

		/**
		 * @brief The TInput instance which should be used for user input.
		 */
		TInput* Input;

		unsigned int WindowWidth;

		unsigned int WindowHeight;

		TScene* CurrentScene = nullptr;

	private:
		void SetupEvents();

		GLFWwindow* CreateWindow(const char* title, unsigned int width, unsigned int height);

		void SetupWindowing();

		FORCEINLINE bool ShouldClose()
		{
			return glfwWindowShouldClose(mWindow);
		}

		TEventListener<float>* OnUpdateListener = nullptr;
		TNotifyListener* OnRenderListener = nullptr;
		GLFWwindow* mWindow = nullptr;
	};

	
	extern TApp* GApp;
}