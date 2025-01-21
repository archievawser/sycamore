#include "Engine/GameObject.h"
#include "Engine/Application.h"
#include <functional>


namespace SYCAMORE_NAMESPACE
{
	TGameObject::TGameObject()
	{ 
		OnUpdate = std::unique_ptr<TEventListener<float>>(App->OnUpdate.Connect(std::bind_front(&TGameObject::Update, this)));
	}


	TGameObject::~TGameObject()
	{ }


	void TGameObject::BeginPlay()
	{
		for (const auto& [typeId, component] : mComponents)
		{
			component->BeginPlay();
		}
	}


	void TGameObject::Update(float dt)
	{
		for (const auto& [typeId, component]: mComponents)
		{
			component->Tick(dt);
		}
	}
}