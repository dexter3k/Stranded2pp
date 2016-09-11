#pragma once

#include "graphics/Color.h"
#include "common/math/Vector2.h"
#include "common/math/Vector3.h"

namespace gfx
{

class Vertex3D
{
public:
	math::Vector3f position;
	math::Vector3f normal;
	Color color;
	math::Vector2f textureCoords;

	Vertex3D();
	Vertex3D(float x, float y, float z, float nX, float nY, float nZ,
		const Color& color, float u, float v);
	Vertex3D(const math::Vector3f& position, const math::Vector3f& normal,
		const Color& color, const math::Vector2f& textureCoords);
	~Vertex3D();

	bool operator==(const Vertex3D& other) const;
	bool operator!=(const Vertex3D& other) const;
};

} // namespace gfx
