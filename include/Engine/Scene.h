#pragma once

#include "Engine/Camera.h"
#include "Engine/GameObject.h"
#include "Graphics/Renderer.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TScene : public TGameObject
	{
	public:
		TScene();

		virtual void Render() = 0;

		/**
		 * @brief The IRenderer derivative used to draw elements to the current window.
		 */
		TGlRenderer Renderer;

		/**
		 * @brief The update event.
		 */
		TEventDispatcher<float> OnUpdate;

		/**
		 * @brief The update event.
		 */
		std::unique_ptr<TNotifyListener> OnRender;

		/**
		 * @brief The camera currently being used when drawing the scene
		 */
		TCamera* CurrentCamera;

		/**
		 * @brief Whether or not the scene has been used as the current scene yet
		 */
		bool UsedBefore = false;
	};
}