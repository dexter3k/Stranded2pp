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

	Vector2() = default;

	Vector2(T x, T y) :
		x(x),
		y(y)
	{}

	Vector2(T value) :
		x(value),
		y(value)
	{}

	Vector2(Vector2<T> const & other) :
		x(other.x),
		y(other.y)
	{}

	Vector2<T> & operator=(Vector2<T> right)
	{
		x = right.x;
		y = right.y;

		return *this;
	}

	template <typename R>
	Vector2<T> & operator=(Vector2<R> right)
	{
		x = static_cast<T>(right.x);
		y = static_cast<T>(right.y);

		return *this;
	}

	T getDotProduct(Vector2<T> other) const
	{
		return (x * other.x) + (y * other.y);
	}

	T getDistanceFrom(Vector2<T> other) const
	{
		return (*this - other).getLength();
	}

	T getLength() const
	{
		return std::sqrt(x*x + y*y);
	}

	// TODO: Investigate this
	bool isEqualTo(const Vector2<T>& other,
		T epsilon = std::numeric_limits<T>::epsilon()) const
	{
		return compareWithEpsilon(x, other.x, epsilon)
				&& compareWithEpsilon(y, other.y, epsilon);
	}

	// TODO: Investigate this
	bool isEqualToRelative(const Vector2<T>& other, T maxRelativeError =
		(std::numeric_limits<T>::epsilon() * static_cast<T>(10))) const
	{
		return compareRelative(x, other.x, maxRelativeError)
				&& compareRelative(y, other.y, maxRelativeError);
	}

	Vector2<T> & invert()
	{
		x = -x;
		y = -y;

		return *this;
	}

	Vector2<T> & normalize()
	{
		T mod = static_cast<T>(1) / getLength();

		x *= mod;
		y *= mod;

		return *this;
	}

	Vector2<T> normalized()
	{
		auto tmp = Vector2<T>(*this);
		tmp.normalize();

		return tmp;
	}

	Vector2<T> operator+(Vector2<T> other) const
	{
		return Vector2<T>(x + other.x, y + other.y);
	}

	Vector2<T> operator-(Vector2<T> other) const
	{
		return Vector2<T>(x - other.x, y - other.y);
	}

	Vector2<T> & operator+=(Vector2<T> other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2<T> & operator-=(Vector2<T> other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2<T> operator-() const
	{
		return Vector2<T>(-x, -y);
	}

	Vector2<T> operator*(T scalar) const
	{
		return Vector2<T>(x * scalar, y * scalar);
	}

	Vector2<T> operator/(T scalar) const
	{
		return Vector2<T>(x / scalar, y / scalar);
	}

	Vector2<T> & operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vector2<T> & operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	bool operator==(Vector2<T> other) const
	{
		assert(std::numeric_limits<T>::is_integer == true);

		return (x == other.x && y == other.y);
	}

	bool operator!=(Vector2<T> other) const
	{
		return !operator==(other);
	}
};

typedef Vector2<double>		Vector2d;
typedef Vector2<float>		Vector2f;
typedef Vector2<int>		Vector2i;
typedef Vector2<unsigned>	Vector2u;

} // namespace math
