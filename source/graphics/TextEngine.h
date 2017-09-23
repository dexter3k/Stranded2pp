#pragma once

#include <string>
#include <unordered_map>

#include "BmpFont.h"
#include "FontType.h"
#include "TextCentering.h"

class Modification;

namespace gfx
{

namespace device
{
	class Device;
}

class TextEngine
{
public:
	TextEngine(device::Device & device, Modification const & modification);

	void drawText(FontType fontType, std::string const & text, math::Vector2i const & position,
		TextCentering centering = NotCentered);
private:
	unsigned calculateTextWidth(BmpFont const & font, std::string const & text);
private:
	device::Device & device;
	std::string const modPath;

	std::unordered_map<FontType, BmpFont> const fonts;
};

} // namespace gfx
