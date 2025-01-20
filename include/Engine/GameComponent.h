#pragma once
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	class TGameComponent
	{
	public:
		virtual void BeginPlay();
		virtual void Tick(double dt);
	};
}