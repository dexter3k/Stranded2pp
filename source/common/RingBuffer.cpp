#include "RingBuffer.h"

#include <cassert>
#include <cstring>
#include <iostream>

RingBuffer::RingBuffer(size_t bufferSize) :
	buffer(new char[bufferSize]),
	bufferSize(bufferSize),
	readPosition(3),
	writePosition(3),
	dataSize(0)
{}

RingBuffer::~RingBuffer()
{
	delete[] buffer;
}

bool RingBuffer::write(const void* data, size_t dataSize)
{
	assert(bufferSize >= dataSize);

	size_t freeSpace = getFreeSpace();
	if (freeSpace < dataSize)
	{
		std::cout << "Buffer is too small" << std::endl;
		return false;
	}

	// Do we overlap?
	if ((writePosition + dataSize) <= bufferSize)
	{
		// No. Just write as is
		memcpy(buffer + writePosition, data, dataSize);

		writePosition += dataSize;

		assert(writePosition <= bufferSize);
		if (writePosition == bufferSize)
		{
			writePosition = 0;
		}
	}
	else
	{
		// Yes. First write until overlap, then remaining
		size_t leadingPartSize = bufferSize - writePosition;
		assert(leadingPartSize < dataSize);

		memcpy(buffer + writePosition, data, leadingPartSize);

		// Write remaining data to buffer beginning
		memcpy(buffer,
			static_cast<const void*>(
				static_cast<const char*>(data) + leadingPartSize),
			dataSize - leadingPartSize);

		writePosition = dataSize - leadingPartSize;
	}

	this->dataSize += dataSize;
	std::cout << "Wrote " << dataSize << " bytes. Data size is now: " <<
		this->dataSize << std::endl;

	return true;
}

bool RingBuffer::read(void* buffer, size_t toRead)
{
	assert(bufferSize >= toRead);

	if (toRead > dataSize)
	{
		// Requesting too much
		return false;
	}

	

	return true;
}

size_t RingBuffer::getFreeSpace() const
{
	return bufferSize - dataSize;
}

void RingBuffer::debug() const
{
	for (size_t i = 0; i < bufferSize; ++i)
	{
		std::cout << static_cast<int>(buffer[i]) << " ";
	}
	std::cout << std::endl;
}
