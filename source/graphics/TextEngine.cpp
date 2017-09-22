#include "TextEngine.h"

#include <iostream>

#include "common/Modification.h"
#include "graphics/device/Device.h"

namespace gfx
{

TextEngine::TextEngine(device::Device & device, Modification const & modification) :
	device(device),
	modPath(modification.getPath()),
	fonts({
		{NormalFont,		{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm.bmp"}},
		{NormalOverFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_over.bmp"}},
		{NormalDarkFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_dark.bmp"}},
		{NormalBadFont,		{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_bad.bmp"}},
		{NormalGoodFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_good.bmp"}},
		{TinyFont,			{device, modPath + "sys/gfx/font_tiny.bmpf", modPath + "sys/gfx/font_tiny.bmp"}},
		{HandwritingFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_handwriting.bmp"}},
	})
{}

void TextEngine::drawText(FontType fontType, std::string const & text,
	math::Vector2i const & position, TextCentering centering)
{
	BmpFont const & font = fonts.at(fontType);

	unsigned const textWidth = calculateTextWidth(font, text);
	unsigned const textHeight = font.getFrameHeight();

	math::Vector2i destination = position;
	if (centering == Centered || centering == CenteredHorizontally) {
		destination.x -= textWidth / 2;
	}
	if (centering == Centered || centering == CenteredVertically) {
		destination.y -= textHeight / 2;
	}

	device.drawText(font, text, destination);
}

unsigned TextEngine::calculateTextWidth(BmpFont const & font, std::string const & text)
{
	unsigned width = 0;
	for (uint8_t character : text) {
		if (character == ' ') {
			width += font.getFrameWidth() / 2;
		} else {
			width += font.getCharacterWidth(character);
		}
	}

	return width;
}

} // namespace gfx
