#pragma once

#include "glm/glm.hpp"
#include "Graphics/Geometry.h"
#include "Graphics/Material.h"
#include "Graphics/Texture.h"
#include "Engine/Transform.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TMeshComponent
	{
	public:
		TMeshComponent(std::shared_ptr<TGeometry> geometry, std::shared_ptr<TMaterial> material);

		FORCEINLINE void SetGeometry(std::shared_ptr<TGeometry> geometry)
		{
			Geometry = geometry;	
		}

		FORCEINLINE void SetMaterial(std::shared_ptr<TMaterial> material)
		{
			Material = material;
		}

		TTransform Transform;
		std::shared_ptr<TGeometry> Geometry = nullptr;
		std::shared_ptr<TMaterial> Material = nullptr;
	};
}