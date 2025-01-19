#include "Engine/Stopwatch.h"

#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	TStopwatch::TStopwatch()
		: mStartTime(mClock.now())
	{	}
}