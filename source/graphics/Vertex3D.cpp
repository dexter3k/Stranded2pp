#include "Vertex3D.h"

namespace gfx
{

Vertex3D::Vertex3D() :
	position(),
	normal(),
	color(),
	textureCoords()
{}

Vertex3D::Vertex3D(float x, float y, float z, float nX, float nY, float nZ,
		const Color& color, float u, float v) :
	position(x, y, z),
	normal(nX, nY, nZ),
	color(color),
	textureCoords(u, v)
{}

Vertex3D::Vertex3D(const math::Vector3f& position, const math::Vector3f& normal,
		const Color& color, const math::Vector2f& textureCoords) :
	position(position),
	normal(normal),
	color(color),
	textureCoords(textureCoords)
{}

Vertex3D::~Vertex3D()
{}

bool Vertex3D::operator==(const Vertex3D& other) const
{
	return (
		position.isEqualToRelative(other.position) &&
		normal.isEqualToRelative(other.normal) &&
		color == other.color &&
		textureCoords == other.textureCoords);
}

bool Vertex3D::operator!=(const Vertex3D& other) const
{
	return !operator==(other);
}

} // namespace gfx
