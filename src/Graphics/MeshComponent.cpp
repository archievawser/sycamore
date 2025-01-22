#include "Graphics/MeshComponent.h"


namespace SYCAMORE_NAMESPACE
{
	TMeshComponent::TMeshComponent(std::shared_ptr<TGeometry> geometry, std::shared_ptr<TMaterial> material)
	{
		SetGeometry(geometry);
		SetMaterial(material);

		int positionAttribLocation = glGetAttribLocation(Material->Shader->GetId(), "position");
		glVertexAttribPointer(positionAttribLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
		glEnableVertexAttribArray(positionAttribLocation);

		int normalAttribLocation = glGetAttribLocation(Material->Shader->GetId(), "normal");
		glVertexAttribPointer(normalAttribLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)12);
		glEnableVertexAttribArray(normalAttribLocation);

		int uvAttribLocation = glGetAttribLocation(Material->Shader->GetId(), "uv");
		glVertexAttribPointer(uvAttribLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)24);
		glEnableVertexAttribArray(uvAttribLocation);
	}
}