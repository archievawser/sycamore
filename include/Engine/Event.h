#pragma once

#include <functional>
#include <vector>
#include <unordered_map>
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	template<typename TEvent>
	class TEventListener;


	template<typename TEvent>
	class TEventDispatcher
	{
		typedef std::function<void(TEvent)> TCallback;

	public:
		FORCEINLINE void Dispatch(TEvent event)
		{
			for (const auto [id, listener] : mListeners)
			{
				listener->Dispatch(event);
			}
		}

		TEventListener<TEvent>* Connect(TCallback callback)
		{
			TEventListener<TEvent>* newListener = new TEventListener<TEvent>(callback);

			Connect(newListener);
			return newListener;
		}

		void Connect(TEventListener<TEvent>* listener)
		{
			unsigned long long id = mNextListenerId++;

			mListeners[id] = listener;
			listener->Connections.push_back({ this, id });
		}

		void Disconnect(unsigned long long id)
		{
			mListeners.erase(id);
		}
	
	private:
		unsigned long long mNextListenerId = 0;
		std::unordered_map<unsigned long long, TEventListener<TEvent>*> mListeners;
	};


	template<typename TEvent>
	class TEventListener
	{
		typedef std::function<void(TEvent)> TCallback;

		struct TConnection
		{
			TEventDispatcher<TEvent>* Target;
			unsigned long long Id;
		};

	public:
		TEventListener()
		{	}

		TEventListener(TCallback callback)
		{ 
			Connect(callback);
		}

		~TEventListener()
		{
			for(TConnection conn: Connections)
			{ 
				conn.Target->Disconnect(conn.Id);
			}
		}

		FORCEINLINE void Dispatch(TEvent event)
		{
			for (TCallback callback : mCallbacks)
			{
				callback(event);
			}
		}

		void Connect(TCallback callback)
		{
			mCallbacks.push_back(callback);
		}

		std::vector<TConnection> Connections;

	private:
		std::vector<TCallback> mCallbacks;
	};
}
