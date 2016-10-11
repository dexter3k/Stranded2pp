#include "IndexBuffer.h"

#include <cassert>

namespace gfx
{

IndexBuffer::IndexBuffer(IndexSize indexSize) :
	indexSize(indexSize),
	indices(nullptr)
{
	switch (indexSize)
	{
		case Index16Bit:
		{
			indices = new IndexArrayImplementation<uint16_t>();

			break;
		}
		case Index32Bit:
		{
			indices = new IndexArrayImplementation<uint32_t>();

			break;
		}
		default:
		{
			assert(!"Unknown index size!");

			break;
		}
	}
}

IndexBuffer::~IndexBuffer()
{
	delete indices;
}

void* IndexBuffer::getData()
{
	return indices->getData();
}

IndexSize IndexBuffer::getIndexSize() const
{
	return indexSize;
}

unsigned IndexBuffer::getSize() const
{
	return indices->getSize();
}

void IndexBuffer::pushBack(const unsigned& value)
{
	indices->pushBack(value);
}

void IndexBuffer::setUsed(unsigned count)
{
	indices->setUsed(count);
}

void IndexBuffer::clear()
{
	indices->clear();
}

} // namespace gfx
