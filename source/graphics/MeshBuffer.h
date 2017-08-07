#pragma once

#include <cstdint>
#include <vector>

#include "HardwareMappingHint.h"
#include "IndexSize.h"
#include "Material.h"
#include "Vertex3D.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace gfx
{

class IndexBuffer;
class VertexBuffer;

class MeshBuffer
{
public:
	MeshBuffer(Vertex3D::VertexType vertexType, IndexSize indexSize);
	~MeshBuffer();

	MeshBuffer(const MeshBuffer&) = delete;

	VertexBuffer& getVertexBuffer() const;
	IndexBuffer& getIndexBuffer() const;

	void setVertexBuffer(VertexBuffer* newVertexBuffer);
	void setIndexBuffer(IndexBuffer* newIndexBuffer);

	const Material& getMaterial() const;
	Material& getMaterial();

	HardwareMappingHint getVertexBufferMappingHint() const;
	HardwareMappingHint getIndexBufferMappingHint() const;

	void setVertexBufferMappingHint(HardwareMappingHint mappingHint);
	void setIndexBufferMappingHint(HardwareMappingHint mappingHint);

	void setDirty();
	void setVertexBufferDirty();
	void setIndexBufferDirty();

	Vertex3D::VertexType getVertexType() const;

	const void* getVertices() const;
	void* getVertices();

	unsigned getVertexCount() const;

	IndexSize getIndexSize() const;

	const void* getIndices() const;
	void* getIndices();

	unsigned getIndexCount() const;

	const math::Vector3f& getPosition(unsigned index) const;
	math::Vector3f& getPosition(unsigned index);

	const math::Vector3f& getNormal(unsigned index) const;
	math::Vector3f& getNormal(unsigned index);

	const math::Vector2f& getTextureCoord(unsigned index) const;
	math::Vector2f& getTextureCoord(unsigned index);
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	Vertex3D::VertexType vertexType;
	IndexSize indexSize;

	HardwareMappingHint vertexBufferMappingHint;
	HardwareMappingHint indexBufferMappingHint;

	Material material;
};

} // namespace gfx
