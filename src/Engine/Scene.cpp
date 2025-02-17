#include "Engine/Scene.h"

#include "Core.h"


namespace SYCAMORE_NAMESPACE 
{
	TScene::TScene()
		: Renderer()
	{
		CurrentCamera = new TCamera;
		CurrentCamera->SetScene(this);

		OnRender = std::unique_ptr<TNotifyListener>(Renderer.OnRender.Connect(std::bind_front(&TScene::Render, this)));
	}
}