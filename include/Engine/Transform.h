#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "Core.h"


class TTransform
{
public:
	TTransform();

	FORCEINLINE const glm::mat4& GetMatrix() 
	{
		if (mRebuildNeeded)
		{
			RebuildTransform();
		}

		return mTransform;
	}

	FORCEINLINE void Rotate(glm::vec3 axis, float angle)
	{
		mRotation = glm::rotate(mRotation, angle, axis);
		mRebuildNeeded = true;
	}
	
	FORCEINLINE void Translate(glm::vec3 translation)
	{
		mPosition += translation;
		mRebuildNeeded = true;
	}

	FORCEINLINE void Scale(glm::vec3 scale)
	{
		mScale = scale;
		mRebuildNeeded = true;
	}

	FORCEINLINE void RebuildTransform()
	{
		mTransform = glm::mat4_cast(mRotation) * glm::translate(glm::scale(glm::mat4(1.0f), mScale), mPosition);
		mRebuildNeeded = false;

		LOG("Rebuilding model matrix");
	}

	FORCEINLINE void SetPosition(glm::vec3 position)
	{
		mPosition = position;
		mRebuildNeeded = true;
	}

	FORCEINLINE void SetRotation(glm::vec3 eulerAngles)
	{
		mRotation = glm::quat(eulerAngles);
		mRebuildNeeded = true;
	}

	FORCEINLINE void LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up = glm::vec3(0, 1, 0))
	{
		mTransform = glm::lookAt(eye, center, up);
	}

private:
	bool mRebuildNeeded = false;
	glm::vec3 mScale = glm::vec3(1.0f);
	glm::quat mRotation = glm::quat(1, 0, 0, 0);
	glm::vec3 mPosition = glm::vec3(0.0f);
	glm::mat4 mTransform = glm::mat4(1.0f);
};