#include "Engine/Input.h"
#include "Engine/Application.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	TInput::TInput(GLFWwindow* window)
		: mLastMousePosition(), mMousePosition(), mMouseDelta()
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, OnMouseMove);
		glfwSetKeyCallback(window, OnKeyEvent);
	}


	void TInput::Update(float dt)
	{
		mMouseDelta = mMousePosition - mLastMousePosition;
		mLastMousePosition = mMousePosition;
	}


	void TInput::OnKeyEvent(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			App->Input->mPressedKeys[key] = true;
			break;
		
		case GLFW_RELEASE:
			App->Input->mPressedKeys[key] = false;
			break;
		}
	}


	void TInput::OnMouseMove(GLFWwindow* window, double x, double y)
	{
		App->Input->mMousePosition = glm::vec2(x, y);
	}
}