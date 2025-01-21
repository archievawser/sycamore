#include <iostream>
#include <memory>
#include "glm/glm.hpp"
#include "Engine/Application.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/Vertex.h"
#include "Graphics/Material.h"
#include "Graphics/Shader.h"
#include "Engine/Event.h"
#include "Core.h"


class TGame : public scm::TApp
{
	typedef scm::TApp Super;

public:
	TGame(const char* name, unsigned int width, unsigned int height)
		: Super(name, width, height), cube(nullptr)
	{	}

	void Start() override
	{
		auto material = std::make_shared<scm::TMaterial>(scm::TShader::Load("../../assets/flat-frag.glsl", "../../assets/flat-vert.glsl"));

		cube = scm::TMeshComponent::Load("../../assets/cube.obj");
		cube->SetMaterial(material);

		Super::Start();
	}

	void Update(float deltaTime) override
	{

	}

	void Render() override
	{
		Renderer.Draw(*cube);
	}

	scm::TMeshComponent* cube;
};


int main()
{
	std::cout << "Running game" << std::endl;

	TGame* game = new TGame("Hello Cube", 1280U, 720U);
	game->Start();
}