#pragma once

#include <cassert>
#include <cmath>
#include <limits>

#include "MathUtility.h"

namespace math
{

template <typename T>
class Vector2
{
public:
	T x;
	T y;

	Vector2() :
		x(),
		y()
	{}

	Vector2(T x, T y) :
		x(x),
		y(y)
	{}

	Vector2(T value) :
		x(value),
		y(value)
	{}

	~Vector2()
	{}

	T getDotProduct(const Vector2<T>& other) const
	{
		return (x * other.x) + (y * other.y);
	}

	T getDistanceFrom(const Vector2<T>& other) const
	{
		return (*this - other).getLength();
	}

	T getLength() const
	{
		return sqrt((x * x) + (y * y));
	}

	bool isEqualTo(const Vector2<T>& other,
		T epsilon = std::numeric_limits<T>::epsilon()) const
	{
		return (
			math::compareWithEpsilon(x, other.x, epsilon) &&
			math::compareWithEpsilon(y, other.y, epsilon));
	}

	Vector2<T>& invert()
	{
		x = -x;
		y = -y;

		return *this;
	}

	Vector2<T>& normalize()
	{
		T mod = static_cast<T>(1) / getLength();

		x *= mod;
		y *= mod;

		return *this;
	}

	Vector2<T> operator+(const Vector2<T>& other) const
	{
		return Vector2<T>(
			x + other.x,
			y + other.y);
	}

	Vector2<T> operator-(const Vector2<T>& other) const
	{
		return Vector2<T>(
			x - other.x,
			y - other.y);
	}

	Vector2<T>& operator+=(const Vector2<T>& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2<T>& operator-=(const Vector2<T>& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2<T> operator-() const
	{
		return Vector2<T>(-x, -y);
	}

	Vector2<T> operator*(const T& scalar) const
	{
		return Vector2<T>(x * scalar, y * scalar);
	}

	Vector2<T> operator/(const T& scalar) const
	{
		return Vector2<T>(x / scalar, y / scalar);
	}

	Vector2<T>& operator*=(const T& scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vector2<T>& operator/=(const T& scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	bool operator==(const Vector2<T>& other) const
	{
		assert(std::numeric_limits<T>::is_integer == true);

		return (
			x == other.x &&
			y == other.y);
	}

	bool operator!=(const Vector2<T>& other) const
	{
		return !operator==(other);
	}
};

typedef Vector2<int>		Vector2i;
typedef Vector2<unsigned>	Vector2u;
typedef Vector2<float>		Vector2f;

} // namespace math
