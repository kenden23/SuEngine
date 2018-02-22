
#pragma once

#include "glm.hpp"

namespace glmex
{
	template<typename genType = float>
	genType half_pi()
	{
		return glm::half_pi<genType>();
	}
}