#pragma once
#include "glm/glm.hpp"
#include "Graphics/Geometry.h"
#include "Graphics/Material.h"
#include "Graphics/Texture.h"
#include "Engine/Transform.h"


class TMeshComponent
{
public:
	TMeshComponent(std::shared_ptr<TGeometry> geometry, std::shared_ptr<TMaterial> material);
	TMeshComponent();
	TMeshComponent(TMeshComponent& other) = delete;
	TMeshComponent& operator=(TMeshComponent& other) = delete;
	~TMeshComponent();

	TTransform Transform;
	std::shared_ptr<TGeometry> Geometry;
	std::shared_ptr<TMaterial> Material;
};