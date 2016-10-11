#include "VertexBuffer.h"

#include <iostream>

namespace gfx
{

VertexBuffer::VertexBuffer(Vertex3D::VertexType vertexType) :
	vertexType(vertexType),
	vertices(nullptr)
{
	switch (vertexType)
	{
		case Vertex3D::Standard:
		{
			vertices = new VertexArrayImplementation<Vertex3D>();

			break;
		}
		case Vertex3D::DoubleTCoords:
		{
			vertices = new VertexArrayImplementation<Vertex3D2TCoords>();

			break;
		}
		default:
		{
			assert(!"Unknown vertex type!");

			break;
		}
	}
}

VertexBuffer::~VertexBuffer()
{
	delete vertices;
}

void* VertexBuffer::getData()
{
	return vertices->getData();
}

Vertex3D::VertexType VertexBuffer::getVertexType() const
{
	return vertexType;
}

unsigned VertexBuffer::getSize() const
{
	return vertices->getSize();
}

void VertexBuffer::pushBack(const Vertex3D& vertex)
{
	vertices->pushBack(vertex);

	std::cout << "PushBack! s:" << vertices->getSize() << std::endl;
}

void VertexBuffer::reserve(unsigned count)
{
	vertices->reserve(count);
}

void VertexBuffer::setUsed(unsigned count)
{
	vertices->setUsed(count);
}

void VertexBuffer::clear()
{
	vertices->clear();
}

} // namespace gfx
