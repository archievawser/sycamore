#include "Engine/GameObject.h"
#include <functional>


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
