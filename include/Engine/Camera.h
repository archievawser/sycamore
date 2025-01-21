#pragma once

#include "glm/glm.hpp"
#include "Engine/GameObject.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TCamera : public TGameObject
	{
		typedef TGameObject Super;

	public:
		TCamera();

		void BeginPlay() override;
		void Update(float dt) override;

		FORCEINLINE const glm::mat4& GetProjectionMatrix()
		{
			return mProjection;
		}

	private:
		float mYaw;
		float mPitch;
		glm::mat4 mProjection;
	};
}