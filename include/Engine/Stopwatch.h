#pragma once
#include <chrono>
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TStopwatch
	{
	public:
		TStopwatch();

		FORCEINLINE double GetElapsed() const
		{
			std::chrono::high_resolution_clock::time_point currentTime = mClock.now();

			constexpr double microsecondsPerSecond = 1'000'000.0;
			const long long numMicroseconds =
				(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - mStartTime)).count();

			return numMicroseconds / microsecondsPerSecond; 
		}

		FORCEINLINE void Restart()
		{
			mStartTime = mClock.now();
		}

	private:
		std::chrono::high_resolution_clock mClock;
		std::chrono::high_resolution_clock::time_point mStartTime;
	};
}