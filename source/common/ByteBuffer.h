#pragma once

class ByteBuffer
{
public:
	ByteBuffer(size_t bufferSize);
	~ByteBuffer();

	bool write(const void* data, size_t dataSize);
private:
	char* buffer;
	size_t bufferSize;
};
