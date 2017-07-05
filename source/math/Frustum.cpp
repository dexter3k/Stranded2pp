#include "Frustum.h"

#include <iostream>

namespace math
{

Frustum::Frustum() :
	planes{},
	points{}
{}

Frustum::Frustum(const Matrix4& projection) :
	planes{},
	points{}
{
	setMatrix(projection);
}

void Frustum::setMatrix(const Matrix4& mat)
{
	planes[Left] = Plane(
		mat(0, 0) + mat(3, 0),
		mat(0, 1) + mat(3, 1),
		mat(0, 2) + mat(3, 2),
		mat(0, 3) + mat(3, 3)).normalize();

	planes[Right] = Plane(
		mat(3, 0) - mat(0, 0),
		mat(3, 1) - mat(0, 1),
		mat(3, 2) - mat(0, 2),
		mat(3, 3) - mat(0, 3)).normalize();

	planes[Bottom] = Plane(
		mat(1, 0) + mat(3, 0),
		mat(1, 1) + mat(3, 1),
		mat(1, 2) + mat(3, 2),
		mat(1, 3) + mat(3, 3)).normalize();

	planes[Top] = Plane(
		mat(3, 0) - mat(1, 0),
		mat(3, 1) - mat(1, 1),
		mat(3, 2) - mat(1, 2),
		mat(3, 3) - mat(1, 3)).normalize();

	planes[Near] = Plane(
		mat(2, 0) + mat(3, 0),
		mat(2, 1) + mat(3, 1),
		mat(2, 2) + mat(3, 2),
		mat(2, 3) + mat(3, 3)).normalize();

	planes[Far] = Plane(
		mat(3, 0) - mat(2, 0),
		mat(3, 1) - mat(2, 1),
		mat(3, 2) - mat(2, 2),
		mat(3, 3) - mat(2, 3)).normalize();

	points[FarTopLeft] =
		planes[Far].getIntersectionPoint(planes[Top], planes[Left]);
	points[FarTopRight] =
		planes[Far].getIntersectionPoint(planes[Top], planes[Right]);
	points[FarBottomLeft] =
		planes[Far].getIntersectionPoint(planes[Bottom], planes[Left]);
	points[FarBottomRight] =
		planes[Far].getIntersectionPoint(planes[Bottom], planes[Right]);

	points[NearTopLeft] =
		planes[Near].getIntersectionPoint(planes[Top], planes[Left]);
	points[NearTopRight] =
		planes[Near].getIntersectionPoint(planes[Top], planes[Right]);
	points[NearBottomLeft] =
		planes[Near].getIntersectionPoint(planes[Bottom], planes[Left]);
	points[NearBottomRight] =
		planes[Near].getIntersectionPoint(planes[Bottom], planes[Right]);

	points[Eye] = planes[Left].getIntersectionPoint(planes[Top], planes[Bottom]);
}

const Vector3f& Frustum::getPoint(Points point) const
{
	return points[point];
}

} // namespace math
