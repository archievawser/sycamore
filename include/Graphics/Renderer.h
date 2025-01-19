#pragma once
#include "Graphics/MeshComponent.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TRenderer
	{
	public:
		TRenderer();

		void Draw(TMeshComponent& target);
	};
}