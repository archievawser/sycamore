#include "Engine/GameObject.h"
#include "Engine/Application.h"
#include "Engine/Scene.h"
#include <functional>


namespace SYCAMORE_NAMESPACE
{
	TGameObject::TGameObject()
		: mScene(nullptr)
	{

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


	void TGameObject::SetScene(TScene* scene)
	{
		mScene = scene;

		OnUpdate = std::unique_ptr<TEventListener<float>>(scene->OnUpdate.Connect(std::bind_front(&TGameObject::Update, this)));
	}
}