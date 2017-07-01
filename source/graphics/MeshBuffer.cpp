#include "MeshBuffer.h"

#include <cassert>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace gfx
{

MeshBuffer::MeshBuffer(Vertex3D::VertexType vertexType, IndexSize indexSize) :
	vertexBuffer(new VertexBuffer(vertexType)),
	indexBuffer(new IndexBuffer(indexSize)),
	vertexType(vertexType),
	indexSize(indexSize),
	vertexBufferMappingHint(HardwareMappingStatic),
	indexBufferMappingHint(HardwareMappingStatic),
	material()
{}

MeshBuffer::~MeshBuffer()
{
	delete vertexBuffer;
	delete indexBuffer;
}

VertexBuffer& MeshBuffer::getVertexBuffer() const
{
	return *vertexBuffer;
}

IndexBuffer& MeshBuffer::getIndexBuffer() const
{
	return *indexBuffer;
}

void MeshBuffer::setVertexBuffer(VertexBuffer*)
{
	assert(!"TODO");
}

void MeshBuffer::setIndexBuffer(IndexBuffer*)
{
	assert(!"TODO");
}

const Material& MeshBuffer::getMaterial() const
{
	return material;
}

Material& MeshBuffer::getMaterial()
{
	return material;
}


HardwareMappingHint MeshBuffer::getVertexBufferMappingHint() const
{
	return vertexBufferMappingHint;
}

HardwareMappingHint MeshBuffer::getIndexBufferMappingHint() const
{
	return indexBufferMappingHint;
}

void MeshBuffer::setVertexBufferMappingHint(HardwareMappingHint mappingHint)
{
	vertexBufferMappingHint = mappingHint;
}

void MeshBuffer::setIndexBufferMappingHint(HardwareMappingHint mappingHint)
{
	indexBufferMappingHint = mappingHint;
}

void MeshBuffer::setDirty()
{
	assert(!"TODO");
}

void MeshBuffer::setVertexBufferDirty()
{
	assert(!"TODO");
}

void MeshBuffer::setIndexBufferDirty()
{
	assert(!"TODO");
}

Vertex3D::VertexType MeshBuffer::getVertexType() const
{
	return vertexType;
}

const void* MeshBuffer::getVertices() const
{
	return vertexBuffer->getData();	
}

void* MeshBuffer::getVertices()
{
	return vertexBuffer->getData();
}

unsigned MeshBuffer::getVertexCount() const
{
	return vertexBuffer->getSize();
}

IndexSize MeshBuffer::getIndexSize() const
{
	return indexSize;
}

const void* MeshBuffer::getIndices() const
{
	return indexBuffer->getData();
}

void* MeshBuffer::getIndices()
{
	return indexBuffer->getData();
}

unsigned MeshBuffer::getIndexCount() const
{
	return indexBuffer->getSize();
}

const math::Vector3f& MeshBuffer::getPosition(unsigned) const
{
	assert(!"TODO");
}

math::Vector3f& MeshBuffer::getPosition(unsigned)
{
	assert(!"TODO");
}

const math::Vector3f& MeshBuffer::getNormal(unsigned) const
{
	assert(!"TODO");
}

math::Vector3f& MeshBuffer::getNormal(unsigned)
{
	assert(!"TODO");
}

const math::Vector2f& MeshBuffer::getTextureCoord(unsigned) const
{
	assert(!"TODO");
}

math::Vector2f& MeshBuffer::getTextureCoord(unsigned)
{
	assert(!"TODO");
}

} // namespace gfx
