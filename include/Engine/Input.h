#pragma once
#include <unordered_map>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Core.h"


class TInput
{
public:
	TInput(GLFWwindow* window);

	void Tick(double dt);

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

private:
	static void onKeyEvent(GLFWwindow* window, int key, int scanCode, int action, int mods);
	static void onMouseMove(GLFWwindow* window, double x, double y);

	std::unordered_map<int, bool> mPressedKeys;
	glm::vec2 mMousePosition;
	glm::vec2 mLastMousePosition;
	glm::vec2 mMouseDelta;
};


extern TInput* Input;