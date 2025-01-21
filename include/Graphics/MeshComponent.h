#pragma once

#include "glm/glm.hpp"
#include "Graphics/Geometry.h"
#include "Graphics/Material.h"
#include "Graphics/Texture.h"
#include "Engine/Transform.h"


namespace SYCAMORE_NAMESPACE
{
	class TMeshComponent
	{
	public:
		TMeshComponent(std::shared_ptr<TGeometry> geometry, std::shared_ptr<TMaterial> material = nullptr);
		TMeshComponent();
		TMeshComponent(TMeshComponent& other) = delete;
		TMeshComponent& operator=(TMeshComponent& other) = delete;
		~TMeshComponent();

		/**
		 * @brief Load a mesh file with Assimp.
		 * @param path 
		 * @return A heap-allocated mesh component - ensure deletion (ideally via a smart pointer) if the mesh has a lifetime.
		 */
		static NODISCARD TMeshComponent* Load(std::string path);
		void SetGeometry(std::shared_ptr<TGeometry> geometry);
		void SetMaterial(std::shared_ptr<TMaterial> material);

		TTransform Transform;
		std::shared_ptr<TGeometry> Geometry = nullptr;
		std::shared_ptr<TMaterial> Material = nullptr;
	};
}