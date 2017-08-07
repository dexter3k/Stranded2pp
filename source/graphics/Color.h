#pragma once

#include <cstdint>

namespace gfx
{

class Color
{
public:
	uint32_t color; // RGBA color ABGR

	Color();
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t aplha = 255);
	~Color();

	uint32_t getAsRGBA32() const;

	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;
	uint8_t getAlpha() const;

	float getClampRed() const;
	float getClampGreen() const;
	float getClampBlue() const;
	float getClampAlpha() const;

	void setRed(uint8_t value);
	void setGreen(uint8_t value);
	void setBlue(uint8_t value);
	void setAlpha(uint8_t value);

	bool operator==(const Color& other) const;
	bool operator!=(const Color& other) const;
};

} // namespace gfx
