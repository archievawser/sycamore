#pragma once

#include <vector>
#include <unordered_map>
#include <concepts>
#include <stack>
#include <type_traits>
#include <cstddef>
#include "Engine/GameObject.h"
#include "Engine/Camera.h"


namespace SYCAMORE_NAMESPACE
{
	template<typename T>
	concept Instantiable = std::is_base_of<TGameObject, T>::value;


	class TWorld
	{
	public:
		TWorld();
		virtual ~TWorld();
		virtual void BeginPlay();
		virtual void Update(float dt);
	
		template<Instantiable T, typename... ArgType>
		T* Instantiate(ArgType... args);

		TCamera* Camera;

	private:
		std::stack<TGameObjectId> mFreeIds;
		std::unordered_map<TGameObjectId, TGameObject*> mGameObjects;
		TGameObjectId mNextUnusedId = 0;
	};


	template<Instantiable T, typename... ArgType>
	T* TWorld::Instantiate(ArgType... args)
	{
		TGameObjectId nextId;

		if (mFreeIds.empty())
		{
			nextId = mNextUnusedId++;
		}
		else
		{
			nextId = mFreeIds.top();
			mFreeIds.pop();
		}

		mGameObjects[nextId] = (TGameObject*)new T(args...);
		mGameObjects[nextId]->Id = nextId;
		return (T*)(mGameObjects[nextId]);
	}
}