#include "GL/glew.h"
#include "Graphics/Renderer.h"
#include "Engine/Camera.h"
#include "Engine/Application.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	void TGlRenderer::Setup()
	{
		assert(("Failed to initialize GLEW", glewInit() == GLEW_OK));

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClearColor(0.04f, 0.04f, 0.04f, 1.0f);
		glEnable(GL_MULTISAMPLE);
	}


	void TGlRenderer::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		OnRender.Dispatch();
	}


	void TGlRenderer::Draw(TMeshComponent& target)
	{
		target.Geometry->Bind();
		target.Material->Shader->Bind();

		// Set model-view-projection matrix
		glm::mat4 mvp = GApp->CurrentCamera->GetProjectionMatrix() * GApp->CurrentCamera->Transform.GetMatrix() * target.Transform.GetMatrix();
		target.Material->Shader->SetUniform("mvp", mvp);

		// Bind textures to their slots
		for (const auto& [index, texture]: target.Material->Textures)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			texture->Bind();

			target.Material->Shader->SetUniform(target.Material->TextureUniformNames[index], index);
		}

		glDrawElements(GL_TRIANGLES, target.Geometry->GetVertexCount(), GL_UNSIGNED_INT, nullptr);
	}
}