#pragma once

#include <cmath>

namespace math
{
	const float pi = 3.1415927410125732421875f;

	template <typename T>
	inline bool compareWithEpsilon(T left, T right, T epsilon)
	{
		return std::abs(left - right) <= epsilon;
	}
} // namespace math
