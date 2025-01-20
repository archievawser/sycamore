#include "Graphics/MeshComponent.h"


namespace SYCAMORE_NAMESPACE
{
	TMeshComponent::TMeshComponent(std::shared_ptr<TGeometry> geometry, std::shared_ptr<TMaterial> material)
		: Geometry(geometry), Material(material)
	{
	}


	TMeshComponent::TMeshComponent()
		: Geometry(), Material()
	{
	}

	TMeshComponent::~TMeshComponent()
	{
	}
}