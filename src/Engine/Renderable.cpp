#include "Engine/Renderable.h"
#include "Engine/Notify.h"
#include "Engine/Scene.h"


namespace SYCAMORE_NAMESPACE
{
	TRenderable::TRenderable(TScene* parentScene)
	{
		mRenderListener = std::unique_ptr<TNotifyListener>(parentScene->Renderer.OnRender.Connect(std::bind_front(&TRenderable::Render, this)));
	}
}