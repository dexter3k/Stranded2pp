#include "BmpFont.h"

#include "common/FileSystem.h"
#include "common/ByteBuffer.h"
#include "graphics/device/Device.h"

namespace gfx
{

BmpFont::BmpFont(device::Device & device, std::string const & bmpfFilename,
		std::string const & bmpFilename) :
	device(device),
	bmpFilename(bmpFilename),
	texture(device.loadTextureFromFile(bmpFilename, false, true)),
	frameCount(0),
	frameWidth(0),
	frameHeight(0),
	indexes(),
	charSizes()
{
	loadFontFile(bmpfFilename);
}

BmpFont::BmpFont(BmpFont const & other) :
	device(other.device),
	bmpFilename(other.bmpFilename),
	texture(device.grabTexture(bmpFilename)),
	frameCount(other.frameCount),
	frameWidth(other.frameWidth),
	frameHeight(other.frameHeight),
	indexes(other.indexes),
	charSizes(other.charSizes)
{}

BmpFont::~BmpFont()
{
	device.releaseTexture(bmpFilename);
}

void BmpFont::loadFontFile(std::string const & filename)
{
	if (!fs::checkFileExists(filename)) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": file does not exist");
	}

	ByteBuffer buffer(fs::getFileSize(filename));
	if (!fs::loadFile(filename, buffer)) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": io error");
	}

	try {
		buffer.readLine(); // skip header

		frameCount = buffer.readUint16();
		frameWidth = buffer.readUint16();
		frameHeight = buffer.readUint16();

		for (uint16_t i = 0; i < frameCount; ++i) {
			uint8_t character = buffer.readUint8();

			indexes[character] = i;
			charSizes[character] = buffer.readUint16();
		}
	} catch (std::runtime_error & e) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": data error");
	}
}

} // namespace gfx
