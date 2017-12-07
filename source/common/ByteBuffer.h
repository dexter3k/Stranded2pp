#pragma once

#include <cstdint>
#include <string>
#include <vector>

class ByteBuffer
{
public:
	ByteBuffer() = default;
	ByteBuffer(std::size_t size);
	ByteBuffer(std::vector<uint8_t> data);

	uint8_t readUint8();
	uint16_t readUint16();
	uint32_t readUint32();
	uint64_t readUint64();

	int8_t readInt8() { return static_cast<int8_t>(readUint8()); };
	int16_t readInt16() { return static_cast<int16_t>(readUint16()); };
	int32_t readInt32() { return static_cast<int32_t>(readUint32()); };
	int64_t readInt64() { return static_cast<int64_t>(readUint64()); };

	float readFloat();
	double readDouble();

	std::string readString(std::size_t size);
	std::string readCString();
	std::string readLine();

	void read(void * buffer, std::size_t count, bool reverseByteOrder = false);
	void write(void * buffer, std::size_t count, bool reverseByteOrder = false);

	void skip(std::size_t count);

	std::size_t bytesLeftForReading() const { return data.size() - readPosition; };
	std::size_t bytesLeftForWriting() const { return data.size() - writePosition; };
private:
	std::vector<uint8_t> data;

	std::size_t readPosition;
	std::size_t writePosition;
};
