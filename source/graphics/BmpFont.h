#pragma once

#include <array>
#include <string>

#include "Texture.h"

namespace gfx
{

namespace device
{
	class Device;
}

class BmpFont
{
public:
	BmpFont(device::Device & device, std::string const & bmpFilename,
		std::string const & bmpfFilename);
	~BmpFont();

	Texture * getTexture() { return texture; };

	unsigned getFrameCount() const { return frameCount; };
	unsigned getFrameWidth() const { return frameWidth; };
	unsigned getFrameHeight() const { return frameHeight; };

	unsigned getCharacterIndex(uint8_t character) const { return indexes[character]; };
	unsigned getCharacterWidth(uint8_t character) const { return charSizes[character]; };
private:
	void loadFontFile(std::string const & filename);
private:
	device::Device & device;
	std::string const bmpFilename;
	Texture * texture;

	unsigned frameCount;
	unsigned frameWidth;
	unsigned frameHeight;

	std::array<unsigned, 256> indexes;
	std::array<unsigned, 256> charSizes;
};

} // namespace gfx
