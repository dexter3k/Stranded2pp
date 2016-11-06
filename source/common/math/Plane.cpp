#include "Plane.h"

#include <iostream>

#include "common/math/MathUtility.h"

namespace math
{

Plane::Plane() :
	n(),
	d()
{}

Plane::Plane(const Vector3f& n, float d) :
	n(n),
	d(d)
{}

Plane::Plane(float a, float b, float c, float d) :
	n(a, b, c),
	d(d)
{}

Plane& Plane::operator=(const Plane& other)
{
	n = other.n;
	d = other.d;

	return *this;
}

Plane& Plane::normalize()
{
	float scale = 1.0f / n.getLength();

	n *= scale;
	d *= scale;

	return *this;
}

Vector3f Plane::getIntersectionPoint(const Plane& second, const Plane& third)
	const
{
	float denominator = n.getDotProduct(second.n.getCrossProduct(third.n));
	if (compareRelative(denominator, 0.0f))
	{
		return Vector3f(1.0f / 0.0f); // Inf
	}

	return Vector3f(
		(second.n.getCrossProduct(third.n) * -d -
			third.n.getCrossProduct(this->n) * second.d -
			this->n.getCrossProduct(second.n) * third.d) / denominator);
}

} // namespace math
