#include <iostream>
#include <memory>
#include <string>
#include "glm/glm.hpp"
#include "Engine/Application.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/Vertex.h"
#include "Graphics/Material.h"
#include "Graphics/Shader.h"
#include "Graphics/Geometry.h"
#include "Engine/Event.h"
#include "Engine/Assets.h"
#include "Core.h"


class TGame : public scm::TApp
{
	typedef scm::TApp Super;

public:
	TGame(const char* name, unsigned int width, unsigned int height)
		: Super(name, width, height), cube(nullptr), skybox(nullptr)
	{	}

	void Start() override
	{
		scm::TAssetManager::Directory = "../assets/";
		auto material = scm::TAssetManager::Load<scm::TMaterial>("flat.glsl");
		auto skymaterial = scm::TAssetManager::Load<scm::TMaterial>("atmosphere.glsl");

		std::shared_ptr<scm::TGeometry> geom(scm::TAssetManager::Load<scm::TGeometry>("cube.obj"));
		cube = new scm::TMeshComponent(geom, material);

		std::shared_ptr<scm::TGeometry> skygeom(scm::TAssetManager::Load<scm::TGeometry>("icosphere.obj"));
		skybox = new scm::TMeshComponent(skygeom, skymaterial);

		skybox->Transform.Scale(glm::vec3(500.0f));

		Super::Start();
	}

	void Update(float deltaTime) override
	{
		constexpr float rotSpeed = 0.5f;

		cube->Transform.Rotate(glm::vec3(1.0f), rotSpeed * deltaTime);

		Super::Update(deltaTime);
	}

	void Render() override
	{
		Renderer.Draw(*cube);
		Renderer.Draw(*skybox);

		Super::Render();
	}

	scm::TMeshComponent* cube;
	scm::TMeshComponent* skybox;
};


int main()
{
	std::cout << "Running game" << std::endl;

	TGame* game = new TGame("Hello Cube", 1920U, 1080U);
	game->Start();
}