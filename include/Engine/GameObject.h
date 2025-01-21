#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Engine/GameComponent.h"
#include "Engine/Transform.h"
#include "Engine/Event.h"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	typedef int TGameObjectId;


	class TGameObject
	{
		typedef TGameObject Super;

	public:
		TGameObject();
		virtual ~TGameObject();

		virtual void BeginPlay();
		virtual void Update(float dt);

		template<typename ComponentType, typename... ArgType>
		void AddComponent(ArgType&&... constructorArgs)
		{
			// Ensure there is only one component of any component type
			assert(mComponents.find(typeid(ComponentType)) == mComponents.end());

			mComponents[typeid(ComponentType)] = new ComponentType(constructorArgs...);
		}

		TTransform Transform;
		TGameObjectId Id;
		std::unique_ptr<TEventListener<float>> OnUpdate;

	private:
		std::unordered_map<std::type_index, TGameComponent*> mComponents;
	};
}