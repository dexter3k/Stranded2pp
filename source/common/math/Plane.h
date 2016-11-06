#pragma once

#include "common/math/Vector3.h"

namespace math
{

class Plane
{
public:
	Vector3f n;
	float d;

	Plane();
	Plane(const Vector3f& n, float d);
	Plane(float a, float b, float c, float d);

	Plane& operator=(const Plane& other);

	Plane& normalize();

	Vector3f getIntersectionPoint(const Plane& second, const Plane& third)
		const;
};

} // namespace math
