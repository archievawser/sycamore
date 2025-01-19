#include <iostream>
#include "glm/glm.hpp"
#include "Engine/Application.h"
#include "Engine/Event.h"
#include "Core.h"


class TGame : public scm::TApp
{
	typedef scm::TApp Super;

public:
	TGame(const char* name, unsigned int width, unsigned int height)
		: Super(name, width, height)
	{	}

	void Update(float deltaTime) override
	{
		std::cout << "Updating" << std::endl;
	}
};


int main()
{
	std::cout << "Running game" << std::endl;

	TGame* game = new TGame("Hello Cube", 1280U, 720U);
	game->Start();

	std::cout << "Exiting game" << std::endl;
}