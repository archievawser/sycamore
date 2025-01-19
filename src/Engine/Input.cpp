#include "Engine/Input.h"
#include "Core.h"


TInput::TInput(GLFWwindow* window)
	: mLastMousePosition(), mMousePosition(), mMouseDelta()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetKeyCallback(window, onKeyEvent);
}


void TInput::Tick(double dt)
{
	mMouseDelta = mMousePosition - mLastMousePosition;
	mLastMousePosition = mMousePosition;
}


void TInput::onKeyEvent(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		Input->mPressedKeys[key] = true;
		break;
		
	case GLFW_RELEASE:
		Input->mPressedKeys[key] = false;
		break;
	}
}


void TInput::onMouseMove(GLFWwindow* window, double x, double y)
{
	Input->mMousePosition = glm::vec2(x, y);
}


TInput* Input = nullptr;