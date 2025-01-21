#pragma once

#include <functional>
#include <vector>
#include <unordered_map>
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TNotifyListener;


	class TNotifyDispatcher
	{
		typedef std::function<void()> TCallback;

	public:
		void Dispatch();

		TNotifyListener* Connect(TCallback callback);

		void Connect(TNotifyListener* listener);

		void Disconnect(unsigned long long id);

	private:
		unsigned long long mNextListenerId = 0;
		std::unordered_map<unsigned long long, TNotifyListener*> mListeners;
	};


	class TNotifyListener
	{
		typedef std::function<void()> TCallback;

		struct TConnection
		{
			TNotifyDispatcher* Target;
			unsigned long long Id;
		};

	public:
		TNotifyListener()
		{
		}

		TNotifyListener(TCallback callback)
		{
			Connect(callback);
		}

		~TNotifyListener()
		{
			for (TConnection conn : Connections)
			{
				conn.Target->Disconnect(conn.Id);
			}
		}

		FORCEINLINE void Dispatch()
		{
			for (TCallback callback : mCallbacks)
			{
				callback();
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
