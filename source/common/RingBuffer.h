#pragma once

#include <cstdio>
#include <string>
#include <vector>

// TODO: improve for readability
// TODO: rewrite and rename to just (Byte)Buffer?
// Cuz name is kinda misleading and reading/writing looks dope af
// See engine/SaveGameUtils.cpp for example of code should NOT look like

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
	size_t getDataSize() const;

	bool readBool(bool& value);
	bool readUint8(uint8_t& value);
	bool readUint16(uint16_t& value);
	bool readUint32(uint32_t& value);
	bool readFloat(float& value);

	bool readNewlineTerminatedString(std::string& string);
	bool readLengthPrefixedString(std::string& string);

	void debug() const;
private:
	bool silentRead(void* buffer, std::size_t toRead, std::size_t& readPointer) const;
private:
	std::vector<uint8_t> buffer;

	std::size_t readPosition;
	std::size_t writePosition;
	std::size_t dataSize;
};
