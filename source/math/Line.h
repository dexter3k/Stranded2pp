#pragma once

#include "math/Vector3.h"

namespace math
{

class Line
{
public:
	math::Vector3f o;
	math::Vector3f d;

	Line();
	Line(const math::Vector3f& o, const math::Vector3f& d);

	math::Vector3f operator*(float q) const;
};

} // namespace math
