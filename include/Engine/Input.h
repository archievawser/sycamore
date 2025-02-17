#pragma once

#include <unordered_map>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Engine/Event.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TInput
	{
	public:
		TInput(GLFWwindow* window);

		void Update(float dt);

		FORCEINLINE glm::vec2 GetMousePosition()
		{
			return mMousePosition;
		}

		FORCEINLINE glm::vec2 GetMouseDelta()
		{
			return mMouseDelta;
		}

		FORCEINLINE bool IsKeyDown(int keyCode)
		{
			return mPressedKeys.find(keyCode) != mPressedKeys.end() && mPressedKeys[keyCode];
		}

		TEventListener<float>* OnUpdateListener;

	private:
		static void OnKeyEvent(GLFWwindow* window, int key, int scanCode, int action, int mods);

		static void OnMouseMove(GLFWwindow* window, double x, double y);

		std::unordered_map<int, bool> mPressedKeys;
		glm::vec2 mMousePosition;
		glm::vec2 mLastMousePosition;
		glm::vec2 mMouseDelta;
	};
}