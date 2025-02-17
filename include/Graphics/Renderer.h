#pragma once

#include "Graphics/MeshComponent.h"
#include "Engine/Notify.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class IRenderer
	{
	public:
		virtual void Setup() = 0;

		virtual void Render() = 0;

		virtual void Draw(TMeshComponent& target) = 0;

		TNotifyDispatcher OnRender;
	};


	class TGlRenderer : public IRenderer
	{
	public:
		void Setup() override;

		void Render() override;

		void Draw(TMeshComponent& target) override;
	};
}