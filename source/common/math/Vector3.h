#pragma once

#include <cassert>
#include <cmath>
#include <limits>

#include "MathUtility.h"

namespace math
{

template <typename T>
class Vector3
{
public:
	T x;
	T y;
	T z;

	Vector3() :
		x(),
		y(),
		z()
	{}

	Vector3(T x, T y, T z) :
		x(x),
		y(y),
		z(z)
	{}

	Vector3(T value) :
		x(value),
		y(value),
		z(value)
	{}

	~Vector3()
	{}

	Vector3<T> getCrossProduct(const Vector3<T>& other) const
	{
		return Vector3<T>(
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x));
	}

	T getDotProduct(const Vector3<T>& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	T getDistanceFrom(const Vector3<T>& other) const
	{
		return ((*this) - other).getLength();
	}

	T getLength() const
	{
		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	bool isEqualTo(const Vector3<T>& other,
		T epsilon = std::numeric_limits<T>::epsilon()) const
	{
		return (
			math::compareWithEpsilon(x, other.x, epsilon) &&
			math::compareWithEpsilon(y, other.y, epsilon) &&
			math::compareWithEpsilon(z, other.z, epsilon));
	}

	Vector3<T>& invert()
	{
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	Vector3<T>& normalize()
	{
		T mod = static_cast<T>(1) / getLength();

		x *= mod;
		y *= mod;
		z *= mod;

		return *this;
	}

	Vector3<T> operator+(const Vector3<T>& other) const
	{
		return Vector3<T>(
			x + other.x,
			y + other.y,
			z + other.z);
	}

	Vector3<T> operator-(const Vector3<T>& other) const
	{
		return Vector3<T>(
			x - other.x,
			y - other.y,
			z - other.z);
	}

	Vector3<T>& operator+=(const Vector3<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vector3<T>& operator-=(const Vector3<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vector3<T> operator-() const
	{
		return Vector3<T>(-x, -y, -z);
	}

	Vector3<T> operator*(const T& scalar) const
	{
		return Vector3<T>(x * scalar, y * scalar, z * scalar);
	}

	Vector3<T> operator/(const T& scalar) const
	{
		return Vector3<T>(x / scalar, y / scalar, z / scalar);
	}

	Vector3<T>& operator*=(const T& scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	Vector3<T>& operator/=(const T& scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	bool operator==(const Vector3<T>& other) const
	{
		assert(std::numeric_limits<T>::is_integer == true);

		return (
			x == other.x &&
			y == other.y &&
			z == other.z);
	}

	bool operator!=(const Vector3<T>& other) const
	{
		return !operator==(other);
	}
};

typedef Vector3<float> Vector3f;

} // namespace math
