#pragma once

#include <cstdio> //size_t
#include <string>

// TODO: improve for readability

// First and main rule: if error occurs, no changes are applied to container

class RingBuffer
{
public:
	RingBuffer(size_t bufferSize);
	~RingBuffer();

	bool write(const void* data, size_t dataSize);
	bool read(void* buffer, size_t toRead);
	bool read(RingBuffer& buffer, size_t toRead);

	//void allocateMore(size_t byteCount);

	size_t getFreeSpace() const;

	bool readBool(bool& value);
	bool readUint16(uint16_t& value);
	bool readFloat(float& value);

	bool readNewlineTerminatedString(std::string& string);

	void debug() const;
private:
	bool silentRead(void* buffer, size_t toRead, size_t& readPointer) const;
private:
	char* buffer;
	size_t bufferSize;

	size_t readPosition;
	size_t writePosition;
	size_t dataSize;
};
