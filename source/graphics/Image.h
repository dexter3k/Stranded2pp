#pragma once

#include <SFML/Graphics/Image.hpp>

#include "Color.h"

#include "math/Vector2.h"

namespace gfx
{

class Image
{
public:
	Image();
	~Image();

	void create(const math::Vector2u& size,
		const Color& color = Color(255, 32, 128));

	bool loadFromFile(const std::string& filename);
	bool saveToFile(const std::string& filename) const;

	math::Vector2u getSize() const;

	const void* getRawData() const;

	void flipVertically();
	void flipHorizontally();

	void applyColorKey(const Color& color = Color(255, 0, 255));

	void setPixel(unsigned x, unsigned y, const Color& color);
private:
	sf::Image image;
};

} // namespace gfx
