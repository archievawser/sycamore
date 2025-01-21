#pragma once

#include "glm/glm.hpp"
#include "Core.h"


namespace SYCAMORE_NAMESPACE
{
	struct TVertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 Uv;
	};
}