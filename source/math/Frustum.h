#pragma once

#include "math/Matrix4.h"
#include "math/Plane.h"
#include "math/Vector3.h"

namespace math
{

class Frustum
{
public:
	enum Planes
	{
		// Optimised order
		Left = 0,
		Right,
		Far,
		Top,
		Bottom,
		Near
	};

	enum Points
	{
		FarTopLeft,
		FarTopRight,
		FarBottomLeft,
		FarBottomRight,
		NearTopLeft,
		NearTopRight,
		NearBottomLeft,
		NearBottomRight,
		Eye
	};
public:
	Frustum();
	Frustum(const Matrix4& projection);

	void setMatrix(const Matrix4& mat);

	const Vector3f& getPoint(Points point) const;
private:
	Plane planes[6];
	Vector3f points[9];
};

} // namespace math
