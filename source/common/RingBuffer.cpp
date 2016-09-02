#include "RingBuffer.h"

#include <cassert>
#include <cstring>
#include <iostream>

RingBuffer::RingBuffer(size_t bufferSize) :
	buffer(new char[bufferSize]),
	bufferSize(bufferSize),
	readPosition(0),
	writePosition(0),
	dataSize(0)
{
#ifndef NDEBUG
	// Initialize each value, so that valgrind wont complain without reason
	// in RingBuffer::debug(void) const
	// In normal conditions uninitialized data is never visible to user
	for (unsigned i = 0; i < bufferSize; ++i)
	{
		buffer[i] = 0;
	}
#endif
}

RingBuffer::~RingBuffer()
{
	delete[] buffer;
}

bool RingBuffer::write(const void* data, size_t dataSize)
{
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
		memcpy(buffer, static_cast<const char*>(data) + leadingPartSize,
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
	// dataSize is confusing. Especially after "write"- function
	if (toRead > dataSize)
	{
		std::cout << "Requested to read too much" << std::endl;
		// Requesting too much
		return false;
	}

	// Overlap?
	if ((readPosition + toRead) <= bufferSize)
	{
		// No.

		memcpy(buffer, this->buffer + readPosition, toRead);

		readPosition += toRead;

		assert(readPosition <= bufferSize);
		if (readPosition == bufferSize)
		{
			readPosition = 0;
		}
	}
	else
	{
		// Yes.

		size_t leadingPartSize = bufferSize - readPosition;
		assert(leadingPartSize < toRead);

		memcpy(buffer, this->buffer + readPosition, leadingPartSize);

		// Read remaining data
		memcpy(static_cast<char*>(buffer) + leadingPartSize, this->buffer,
			toRead - leadingPartSize);
		readPosition = toRead - leadingPartSize;
	}

	dataSize -= toRead;
	std::cout << "Readed " << toRead << " bytes. Data size is now: " <<
		this->dataSize << std::endl;

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
