#include "Color.h"

namespace gfx
{

Color::Color() :
	color()
{}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
	color(alpha << 24 | blue << 16 | green << 8 | red)
{}

Color::~Color()
{}

uint8_t Color::getRed() const
{
	return (color) & 0xff;
}

uint8_t Color::getGreen() const
{
	return (color >> 8) & 0xff;
}

uint8_t Color::getBlue() const
{
	return (color >> 16) & 0xff;
}

uint8_t Color::getAlpha() const
{
	return (color >> 24) & 0xff;
}

float Color::getClampRed() const
{
	return static_cast<float>(getRed()) / 255.0f;
}

float Color::getClampGreen() const
{
	return static_cast<float>(getGreen()) / 255.0f;
}

float Color::getClampBlue() const
{
	return static_cast<float>(getBlue()) / 255.0f;
}

float Color::getClampAlpha() const
{
	return static_cast<float>(getAlpha()) / 255.0f;
}

void Color::setRed(uint8_t value)
{
	color = (value) | (color & 0x00ffffff);
}

void Color::setGreen(uint8_t value)
{
	color = (value << 8) | (color & 0xff00ffff);
}

void Color::setBlue(uint8_t value)
{
	color = (value << 16) | (color & 0xffff00ff);
}

void Color::setAlpha(uint8_t value)
{
	color = (value << 24) | (color & 0xffffff00);
}

bool Color::operator==(const Color& other) const
{
	return color == other.color;
}

bool Color::operator!=(const Color& other) const
{
	return color != other.color;
}

} // namespace gfx
