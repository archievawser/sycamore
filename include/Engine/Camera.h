#pragma once
#include "glm/glm.hpp"
#include "Engine/GameObject.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TCamera : public TGameObject
	{
	public:
		TCamera();

		void BeginPlay() override;
		void Tick(double dt) override;

		FORCEINLINE const glm::mat4& GetProjectionMatrix()
		{
			return mProjection;
		}

		static TCamera CurrentCamera;

	private:
		float mYaw;
		float mPitch;
		glm::mat4 mProjection;
	};
}