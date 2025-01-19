#include "Core.h"
#include "Engine/Event.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"


struct GLFWwindow;


namespace SYCAMORE_NAMESPACE
{
	/**
	 * @brief The abstract root class of a Sycamore application.
	 */
	class TApp
	{
	public:
		TApp(const char* title, unsigned int width, unsigned int height);

		/**
		 * @brief Called immediately after the engine has initialized
		 */
		virtual void Start();
		/**
		 * @brief Called once per frame, prior to rendering
		 */
		virtual void Tick();
		virtual void Update(float deltaTime);

		TEventDispatcher<float> OnUpdate;

	private:
		void SetupEvents();
		GLFWwindow* CreateWindow(const char* title, unsigned int width, unsigned int height);
		void SetupWindowing();

		FORCEINLINE bool ShouldClose()
		{
			return glfwWindowShouldClose(mWindow);
		}

		TEventListener<float>* OnUpdateListener = nullptr;
		GLFWwindow* mWindow = nullptr;
	};

	
	extern TApp* App;
}