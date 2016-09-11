#pragma once

#include "Vector2.h"

namespace math
{

template <typename T>
class Rect
{
public:
	Vector2<T> upperLeft;
	Vector2<T> lowerRight;

	Rect() :
		upperLeft(),
		lowerRight()
	{}

	Rect(T x, T y, T x2, T y2) :
		upperLeft(x, y),
		lowerRight(x2, y2)
	{}

	Rect(const Vector2<T>& upperLeft, const Vector2<T>& lowerRight) :
		upperLeft(upperLeft),
		lowerRight(lowerRight)
	{}

	~Rect()
	{}

	void clipAgainst(const Rect<T>& other)
	{
		if (other.lowerRight.x < lowerRight.x)
		{
			lowerRight.x = other.lowerRight.x;
		}
		if (other.lowerRight.y < lowerRight.y)
		{
			lowerRight.y = other.lowerRight.y;
		}
		if (other.upperLeft.x > upperLeft.x)
		{
			upperLeft.x = other.upperLeft.x;
		}
		if (other.upperLeft.y > upperLeft.y)
		{
			upperLeft.y = other.upperLeft.y;
		}

		if (upperLeft.y > lowerRight.y)
		{
			upperLeft.y = lowerRight.y;
		}
		if (upperLeft.x > lowerRight.x)
		{
			upperLeft.x = lowerRight.x;
		}
	}

	T getWidth() const
	{
		return lowerRight.x - upperLeft.x;
	}

	T getHeight() const
	{
		return lowerRight.y - upperLeft.y;
	}

	bool isValid() const
	{
		return ((lowerRight.x >= upperLeft.x) &&
			(lowerRight.y >= upperLeft.y));
	}
};

typedef Rect<int> Recti;

} // namespace math
