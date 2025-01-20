#include "Engine/World.h"


namespace SYCAMORE_NAMESPACE
{
	TWorld::TWorld()
	{
		Camera = Instantiate<TCamera>();
	}


	TWorld::~TWorld()
	{ 
		delete Camera;
	}


	void TWorld::BeginPlay()
	{

	}


	void TWorld::Tick(double dt)
	{
		for (auto [id, gameObject] : mGameObjects)
		{
			gameObject->Tick(dt);
		}
	}
}