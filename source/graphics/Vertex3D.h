#pragma once

#include "graphics/Color.h"
#include "common/math/Vector2.h"
#include "common/math/Vector3.h"

namespace gfx
{

class Vertex3D
{
public:
	enum VertexType
	{
		Standard,
		DoubleTCoords
	};
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
	virtual ~Vertex3D();

	bool operator==(const Vertex3D& other) const;
	bool operator!=(const Vertex3D& other) const;
};

class Vertex3D2TCoords : public Vertex3D
{
	typedef Vertex3D super;
public:
	math::Vector2f textureCoords2; // Second set of texture coordinates

	Vertex3D2TCoords();
	Vertex3D2TCoords(float x, float y, float z, float nX, float nY, float nZ,
		const Color& color, float u, float v, float u2, float v2);
	Vertex3D2TCoords(const math::Vector3f& position, const math::Vector3f& normal,
		const Color& color, const math::Vector2f& textureCoords,
		const math::Vector2f& textureCoords2);
	~Vertex3D2TCoords();

	bool operator==(const Vertex3D2TCoords& other) const;
	bool operator!=(const Vertex3D2TCoords& other) const;
};

} // namespace gfx
