#pragma once

#include <cstdint>
#include <vector>

#include "IndexSize.h"
#include "Material.h"
#include "Vertex3D.h"

namespace gfx
{

class IndexBuffer;

class MeshBuffer
{
public:
	MeshBuffer();
	~MeshBuffer();

	const Material& getMaterial() const;
	Material& getMaterial();

	Vertex3D::VertexType getVertexType() const;

	const void* getVertices() const;
	void* getVertices();

	unsigned getVertexCount() const;

	IndexSize getIndexSize() const;

	const void* getIndices() const;
	void* getIndices();

	unsigned getIndexCount() const;

	const Vector3f& getPosition(unsigned index) const;
	Vector3f& getPosition(unsigned index);

	const Vector3f& getNormal(unsigned index) const;
	Vector3f& getNormal(unsigned index);

	const Vector2f& getTextureCoord(unsigned index) const;
	Vector2f& getTextureCoord(unsigned index);
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
};

} // namespace gfx
