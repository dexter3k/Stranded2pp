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

bool RingBuffer::readBool(bool& value)
{
	return read(&value, 1);
}

bool RingBuffer::readUint16(uint16_t& value)
{
	return read(&value, 2);
}

bool RingBuffer::readFloat(float& value)
{
	return read(&value, 4);
}

bool RingBuffer::readNewlineTerminatedString(std::string& string)
{
	string.clear();

	if (dataSize == 0)
	{
		std::cout << "No data" << std::endl;

		return false;
	}

	size_t silentReadPointer = readPosition;

	char currentByte = 0;
	do
	{
		if (!silentRead(&currentByte, 1, silentReadPointer))
		{
			return false;
		}

		if (currentByte == '\r')
		{
			// Skip carriage return
			continue;
		}
		else if (currentByte != '\n')
		{
			string.push_back(currentByte);
		}
		else
		{
			break;
		}
	}
	while(true);

	readPosition = silentReadPointer;
	dataSize -= string.size();

	std::cout << "Newline string read: '" << string << "'" << std::endl;

	return true;
}

void RingBuffer::debug() const
{
	for (size_t i = 0; i < bufferSize; ++i)
	{
		std::cout << static_cast<int>(buffer[i]) << " ";
	}
	std::cout << std::endl;
}

bool RingBuffer::silentRead(void* buffer, size_t toRead, size_t& readPointer)
	const
{
	assert(readPointer < bufferSize);

	if (toRead > dataSize)
	{
		std::cout << "toRead > dataSize" << std::endl;

		return false;
	}

	// Check for overlap
	if ((readPointer + toRead) <= bufferSize)
	{
		// No.

		memcpy(buffer, this->buffer + readPointer, toRead);

		readPointer += toRead;

		assert(readPointer <= bufferSize);
		if (readPointer == bufferSize)
		{
			readPointer = 0;
		}
	}
	else
	{
		// Yes.

		size_t leadingPartSize = bufferSize - readPointer;
		assert(leadingPartSize < toRead);

		memcpy(buffer, this->buffer + readPointer, leadingPartSize);

		// Read remaining data
		memcpy(static_cast<char*>(buffer) + leadingPartSize, this->buffer,
			toRead - leadingPartSize);
		readPointer = toRead - leadingPartSize;
	}

	std::cout << "Silently readed " << toRead << " bytes" << std::endl;

	return true;
}
