#include "MeshBuffer.h"

#include "IndexBuffer.h"

namespace gfx
{

MeshBuffer::MeshBuffer(IndexSize indexSize) :
	vertices(),
	indexBuffer(new IndexBuffer<indexSize>())
{}

~MeshBuffer()
{
	delete indexBuffer;
}

} // namespace gfx
