#include "Line.h"

namespace math
{

Line::Line() :
	o(),
	d()
{}

Line::Line(const math::Vector3f& o, const math::Vector3f& d) :
	o(o),
	d(d)
{}

math::Vector3f Line::operator*(float q) const
{
	return o + d * q;
}

} // namespace math
