#include <algorithm>
#include "Engine/Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine/Application.h"
#include "Engine/Input.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	TCamera::TCamera()
		: Super(), mPitch(0.0f), mYaw(0.0f)
	{
		mProjection = glm::perspective(70.0f, (float)App->WindowWidth / (float)App->WindowHeight, 1.0f, 1000.0f);
	}


	void TCamera::BeginPlay()
	{
	}


	void TCamera::Update(float dt)
	{
		// TODO: cleanup
		static glm::vec3 position(1.0f);

		glm::vec2 e = App->Input->GetMouseDelta();

		mPitch -= e.y * 0.2f;
		mYaw += e.x * 0.2f;

		mPitch = std::clamp(mPitch, -89.0f, 89.0f);

		float forwardX = std::cos(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
		float forwardY = std::sin(glm::radians(mPitch));
		float forwardZ = std::sin(glm::radians(mYaw)) * std::cos(glm::radians(mPitch));
	
		glm::vec3 forwardDirection (forwardX, forwardY, forwardZ);
		glm::vec3 rightDirection = glm::cross(forwardDirection, glm::vec3(0, 1, 0));

		float horizontalInput = (App->Input->IsKeyDown(GLFW_KEY_D) ? 1 : 0) 
			- (App->Input->IsKeyDown(GLFW_KEY_A) ? 1 : 0);

		float verticalInput = (App->Input->IsKeyDown(GLFW_KEY_W) ? 1 : 0)
			- (App->Input->IsKeyDown(GLFW_KEY_S) ? 1 : 0);
	
		position += (forwardDirection * verticalInput + rightDirection * horizontalInput) * 50.0f * (float)dt;
		Transform.LookAt(position, position + forwardDirection, glm::vec3(0, 1, 0));
	}
}