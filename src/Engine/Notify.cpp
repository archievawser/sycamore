#include "Engine/Notify.h"


namespace SYCAMORE_NAMESPACE
{
	void TNotifyDispatcher::Dispatch()
	{
		for (const auto [id, listener] : mListeners)
		{
			listener->Dispatch();
		}
	}


	TNotifyListener* TNotifyDispatcher::Connect(TCallback callback)
	{
		TNotifyListener* newListener = new TNotifyListener(callback);

		Connect(newListener);
		return newListener;
	}


	void TNotifyDispatcher::Connect(TNotifyListener* listener)
	{
		unsigned long long id = mNextListenerId++;

		mListeners[id] = listener;
		listener->Connections.push_back({ this, id });
	}


	void TNotifyDispatcher::Disconnect(unsigned long long id)
	{
		mListeners.erase(id);
	}
}