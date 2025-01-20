#include "Engine/GameObject.h"
#include <functional>


namespace SYCAMORE_NAMESPACE
{
	TGameObject::TGameObject()
	{ }


	TGameObject::~TGameObject()
	{ }


	void TGameObject::BeginPlay()
	{
		for (const auto& [typeId, component] : mComponents)
		{
			component->BeginPlay();
		}
	}


	void TGameObject::Tick(double dt)
	{
		for (const auto& [typeId, component]: mComponents)
		{
			component->Tick(dt);
		}
	}
}