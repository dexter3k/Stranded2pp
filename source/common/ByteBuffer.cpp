#include "ByteBuffer.h"

#include <stdexcept>

ByteBuffer::ByteBuffer(std::size_t size) :
	ByteBuffer(std::vector<uint8_t>(size))
{}

ByteBuffer::ByteBuffer(std::vector<uint8_t> data) :
	data(std::move(data)),
	readPosition(0),
	writePosition(0)
{}

uint8_t ByteBuffer::readUint8()
{
	uint8_t value = 0;
	read(&value, 1);
	return value;
}

uint16_t ByteBuffer::readUint16()
{
	uint16_t value = 0;
	read(&value, 2);
	return value;
}

uint32_t ByteBuffer::readUint32()
{
	uint32_t value = 0;
	read(&value, 4);
	return value;
}

uint64_t ByteBuffer::readUint64()
{
	uint64_t value = 0;
	read(&value, 8);
	return value;
}

float ByteBuffer::readFloat()
{
	float value = 0.0f;
	read(&value, 4);
	return value;
}

double ByteBuffer::readDouble()
{
	double value = 0.0;
	read(&value, 8);
	return value;
}

std::string ByteBuffer::readString(std::size_t size)
{
	if (size > bytesLeftForReading()) {
		throw std::runtime_error(
			std::string("Buffer underflow of ")
			+ std::to_string(size - bytesLeftForReading())
			+ " bytes");
	}

	auto oldPosition = readPosition;
	readPosition += size;

	return std::string(reinterpret_cast<char const *>(data.data() + oldPosition), size);
}

std::string ByteBuffer::readCString()
{
	std::string value;

	uint8_t byte = 0;
	for (std::size_t i = readPosition; (byte = data[i]) != 0; ++i) {
		if (i >= data.size()) {
			throw std::runtime_error("Reading c-string with no end");
		}

		value += static_cast<char>(data[i]);
	}

	readPosition += value.size() + 1;

	return value;
}

void ByteBuffer::read(void * buffer, std::size_t count, bool reverseByteOrder)
{
	if (count > bytesLeftForReading()) {
		throw std::runtime_error(
			std::string("Buffer underflow of ")
			+ std::to_string(count - bytesLeftForReading())
			+ " bytes");
	}

	if (reverseByteOrder) {
		for (std::size_t i = 0; i < count; ++i) {
			reinterpret_cast<uint8_t *>(buffer)[i] = data[readPosition + count - i - 1];
		}
	} else {
		for (std::size_t i = 0; i < count; ++i) {
			reinterpret_cast<uint8_t *>(buffer)[i] = data[readPosition + i];
		}
	}

	readPosition += count;
}

void ByteBuffer::write(void * buffer, std::size_t count, bool reverseByteOrder)
{
	if (count > bytesLeftForWriting()) {
		throw std::runtime_error(
			std::string("Buffer overflow of ")
			+ std::to_string(count - bytesLeftForWriting())
			+ " bytes");
	}

	if (reverseByteOrder) {
		for (std::size_t i = 0; i < count; ++i) {
			data[writePosition + count - i - 1] = reinterpret_cast<uint8_t *>(buffer)[i];
		}
	} else {
		for (std::size_t i = 0; i < count; ++i) {
			data[writePosition + i] = reinterpret_cast<uint8_t *>(buffer)[i];
		}
	}

	writePosition += count;
}

void ByteBuffer::skip(std::size_t count)
{
	if (count > bytesLeftForReading()) {
		throw std::runtime_error(
			std::string("Buffer underflow of ")
			+ std::to_string(count - bytesLeftForReading())
			+ " bytes");
	}

	readPosition += count;
}
