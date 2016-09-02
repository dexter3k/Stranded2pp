#pragma once

#include <cstdio> //size_t

// TODO: improve for readability

class RingBuffer
{
public:
	RingBuffer(size_t bufferSize);
	~RingBuffer();

	bool write(const void* data, size_t dataSize);
	bool read(void* buffer, size_t toRead);
	bool read(RingBuffer& buffer, size_t toRead);

	size_t getFreeSpace() const;

	void debug() const;
private:
	char* buffer;
	size_t bufferSize;

	size_t readPosition;
	size_t writePosition;
	size_t dataSize;
};
