#pragma once

#include "Engine/GameObject.h"
#include "Engine/Notify.h"
#include "Engine/Scene.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TRenderable : public TGameObject
	{
		typedef TGameObject Super;

	public:
		TRenderable(TScene* parentScene);

		virtual void Render() = 0;

	private:
		std::unique_ptr<TNotifyListener> mRenderListener;
	};
}