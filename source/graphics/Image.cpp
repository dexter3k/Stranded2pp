#include "Image.h"

#include <iostream>

#include <SFML/Graphics/Color.hpp>

namespace gfx
{

Image::Image() :
	image()
{}

Image::~Image()
{}

void Image::create(const math::Vector2u& size, const Color& color)
{
	image.create(size.x, size.y, sf::Color(color.getAsRGBA32()));
}

bool Image::loadFromFile(const std::string& filename)
{
	return image.loadFromFile(filename);;
}

math::Vector2u Image::getSize() const
{
	auto size = image.getSize();

	return math::Vector2u(size.x, size.y);
}

const void* Image::getRawData() const
{
	return image.getPixelsPtr();
}

void Image::flipVertically()
{
	image.flipVertically();
}

void Image::flipHorizontally()
{
	image.flipHorizontally();
}

void Image::applyColorKey(const Color& color)
{
	image.createMaskFromColor(sf::Color(color.getRed(), color.getGreen(),
		color.getBlue()));
}

} // namespace gfx
