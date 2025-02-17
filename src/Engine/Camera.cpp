#include <algorithm>
#include "Engine/Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine/Application.h"
#include "Engine/Input.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	TCamera::TCamera()
		: mPitch(0.0f), mYaw(0.0f)
	{
		mProjection = glm::perspective(70.0f, (float)GApp->WindowWidth / (float)GApp->WindowHeight, 1.0f, 1000.0f);
	}


	void TCamera::BeginPlay()
	{
	}


	void TCamera::Update(float dt)
	{
		// TODO: cleanup
		static glm::vec3 position(1.0f);
		static float targetPitch = 0.0f;
		static float targetYaw = 0.0f;

		glm::vec2 e = GApp->Input->GetMouseDelta();

		targetPitch -= e.y * 0.2f;
		targetYaw += e.x * 0.2f;

		targetPitch = std::clamp(targetPitch, -89.0f, 89.0f);
		mPitch = std::lerp(mPitch, targetPitch, 10.f * dt);
		mYaw = std::lerp(mYaw, targetYaw, 10.f * dt);

		float forwardX = std::cos(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
		float forwardY = std::sin(glm::radians(mPitch));
		float forwardZ = std::sin(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
	
		glm::vec3 forwardDirection (forwardX, forwardY, forwardZ);
		glm::vec3 rightDirection = glm::cross(forwardDirection, glm::vec3(0, 1, 0));

		float horizontalInput = (GApp->Input->IsKeyDown(GLFW_KEY_D) ? 1 : 0) 
			- (GApp->Input->IsKeyDown(GLFW_KEY_A) ? 1 : 0);

		float verticalInput = (GApp->Input->IsKeyDown(GLFW_KEY_W) ? 1 : 0)
			- (GApp->Input->IsKeyDown(GLFW_KEY_S) ? 1 : 0);
	
		position += (forwardDirection * verticalInput + rightDirection * horizontalInput) * 50.0f * (float)dt;
		Transform.LookAt(position, position + forwardDirection, glm::vec3(0, 1, 0));
	}
}