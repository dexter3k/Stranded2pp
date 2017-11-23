#include "RingBuffer.h"

#include <cassert>
#include <cstring>
#include <iostream>

RingBuffer::RingBuffer(std::size_t bufferSize) :
	buffer(bufferSize),
	readPosition(0),
	writePosition(0),
	dataSize(0)
{}

RingBuffer::~RingBuffer()
{}

bool RingBuffer::write(const void* data, size_t dataSize)
{
	size_t freeSpace = getFreeSpace();
	if (freeSpace < dataSize)
	{
		std::cout << "Buffer is too small" << std::endl;
		return false;
	}

	// Do we overlap?
	if ((writePosition + dataSize) <= buffer.size())
	{
		// No. Just write as is
		memcpy(buffer.data() + writePosition, data, dataSize);

		writePosition += dataSize;

		assert(writePosition <= buffer.size());
		if (writePosition == buffer.size())
		{
			writePosition = 0;
		}
	}
	else
	{
		// Yes. First write until overlap, then remaining
		size_t leadingPartSize = buffer.size() - writePosition;
		assert(leadingPartSize < dataSize);

		memcpy(buffer.data() + writePosition, data, leadingPartSize);

		// Write remaining data to buffer beginning
		memcpy(buffer.data(), static_cast<const char*>(data) + leadingPartSize,
			dataSize - leadingPartSize);

		writePosition = dataSize - leadingPartSize;
	}

	this->dataSize += dataSize;
	//std::cout << "Wrote " << dataSize << " bytes. Data size is now: " <<
	//	this->dataSize << std::endl;

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
	if ((readPosition + toRead) <= this->buffer.size())
	{
		// No.

		memcpy(buffer, this->buffer.data() + readPosition, toRead);

		readPosition += toRead;

		assert(readPosition <= this->buffer.size());
		if (readPosition == this->buffer.size())
		{
			readPosition = 0;
		}
	}
	else
	{
		// Yes.

		size_t leadingPartSize = this->buffer.size() - readPosition;
		assert(leadingPartSize < toRead);

		memcpy(buffer, this->buffer.data() + readPosition, leadingPartSize);

		// Read remaining data
		memcpy(static_cast<char*>(buffer) + leadingPartSize, this->buffer.data(),
			toRead - leadingPartSize);
		readPosition = toRead - leadingPartSize;
	}

	dataSize -= toRead;
	//std::cout << "Readed " << toRead << " bytes. Data size is now: " <<
	//	this->dataSize << std::endl;
	
	return true;
}

size_t RingBuffer::getFreeSpace() const
{
	return buffer.size() - dataSize;
}

size_t RingBuffer::getDataSize() const
{
	return dataSize;
}

bool RingBuffer::readBool(bool& value)
{
	return read(&value, 1);
}

bool RingBuffer::readUint8(uint8_t& value)
{
	return read(&value, 1);
}

bool RingBuffer::readUint16(uint16_t& value)
{
	return read(&value, 2);
}

bool RingBuffer::readUint32(uint32_t& value)
{
	return read(&value, 4);
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
	dataSize -= (string.size() + 2); // 2 bytes for \r and \n

	//std::cout << "Newline string read: '" << string << "'" << std::endl;
	//std::cout << "ds: " << dataSize << std::endl;

	return true;
}

bool RingBuffer::readLengthPrefixedString(std::string& string)
{
	string.clear();

	if (dataSize == 0)
	{
		std::cout << "No data" << std::endl;

		return false;
	}

	uint32_t stringSize = 0;
	if (!readUint32(stringSize))
	{
		return false;
	}

	char currentByte = 0;
	for (unsigned i = 0; i < stringSize; ++i)
	{
		if (!read(&currentByte, 1))
		{
			return false;
		}

		string.push_back(currentByte);
	}

	return true;
}

void RingBuffer::debug() const
{
	for (size_t i = 0; i < buffer.size(); ++i)
	{
		std::cout << static_cast<int>(buffer[i]) << " ";
	}
	std::cout << std::endl;
}

bool RingBuffer::silentRead(void* buffer, size_t toRead, size_t& readPointer)
	const
{
	assert(readPointer < this->buffer.size());

	if (toRead > dataSize)
	{
		std::cout << "toRead > dataSize" << std::endl;

		return false;
	}

	// Check for overlap
	if ((readPointer + toRead) <= this->buffer.size())
	{
		// No.

		memcpy(buffer, this->buffer.data() + readPointer, toRead);

		readPointer += toRead;

		assert(readPointer <= this->buffer.size());
		if (readPointer == this->buffer.size())
		{
			readPointer = 0;
		}
	}
	else
	{
		// Yes.

		size_t leadingPartSize = this->buffer.size() - readPointer;
		assert(leadingPartSize < toRead);

		memcpy(buffer, this->buffer.data() + readPointer, leadingPartSize);

		// Read remaining data
		memcpy(static_cast<char*>(buffer) + leadingPartSize, this->buffer.data(),
			toRead - leadingPartSize);
		readPointer = toRead - leadingPartSize;
	}

	//std::cout << "Silently readed " << toRead << " bytes" << std::endl;

	return true;
}
