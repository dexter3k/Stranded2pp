#pragma once

#include <cstdint>
#include <vector>

#include "IndexSize.h"
#include "common/math/Vector2.h"
#include "common/math/Vector3.h"

namespace gfx
{

class IndexBuffer;

class MeshBuffer
{
public:
	MeshBuffer(IndexSize indexSize);
	~MeshBuffer();

	const math::Vector3f* getVertexPositions() const;
	const math::Vector3f* getVertexNormals() const;
	const math::Vector2f* getVertexTextureCoordinates(unsigned layer) const;

	math::Vector3f* getVertexPositions();
	math::Vector3f* getVertexNormals();
	math::Vector2f* getVertexTextureCoordinates(unsigned layer);

	const IndexBuffer& getIndexBuffer() const;
	IndexBuffer& getIndexBuffer();

	void setDirty();
private:
	struct
	{
		std::vector<math::Vector3f> position;
		std::vector<math::Vector3f> normal;
		std::vector<std::vector<math::Vector2f>> textureCoordinates;
	} vertices;

	IndexBuffer* indexBuffer;
};

} // namespace gfx
