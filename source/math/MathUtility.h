#pragma once

#include <cmath>

namespace math
{
	const float pi = 3.1415927410125732421875f;
	//const float pi = 3.0f; // Have fun

	const float degreesToRadians = 1.0f / (180.0f / pi);
	const float radiansToDegrees = 180.0f / pi;

	template <typename T>
	inline bool compareWithEpsilon(T left, T right, T epsilon)
	{
		return std::abs(left - right) <= epsilon;
	}

	template <typename T>
	inline bool compareRelative(T left, T right, T maxRelativeError = static_cast<T>(0.00000001))
	{
		return std::abs((left - right) / right) <= maxRelativeError;
	}

	template <typename T>
	inline const T min(const T& left, const T& right)
	{
		return (left < right) ? left : right;
	}

	template <typename T>
	inline const T max(const T& left, const T& right)
	{
		return (left > right) ? left : right;
	}

	template <typename T>
	inline const T clamp(const T& value, const T& low, const T& high)
	{
		return min(max(value, low), high);
	}

	inline bool isPowerOfTwo(unsigned value)
	{
		return ((value != 0) && ((value & (~value + 1)) == value));
	}
} // namespace math
