#include "Graphics/Renderer.h"
#include "Engine/Camera.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	TRenderer::TRenderer()
	{	}


	void TRenderer::Draw(TMeshComponent& target)
	{
		target.Geometry->Bind();
		target.Material->Shader->Bind();

		// Set model-view-projection matrix
		glm::mat4 mvp = TCamera::CurrentCamera.GetProjectionMatrix() * TCamera::CurrentCamera.Transform.GetMatrix() * target.Transform.GetMatrix();
		target.Material->Shader->SetUniform("mvp", mvp);

		// Bind textures to their slots
		for (const auto& [index, texture]: target.Material->Textures)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			texture->Bind();

			target.Material->Shader->SetUniform(target.Material->TextureUniformNames[index], index);
		}

		glDrawArrays(GL_TRIANGLES, 0, target.Geometry->GetVertexCount());
	}
}