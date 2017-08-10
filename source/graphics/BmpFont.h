#pragma once

#include <string>

namespace gfx
{

class Device;

class BmpFont
{
public:
	//BmpFont(gfx::Device & device, std::string const & bmp, std::string const & bmpf);

	Texture * getTexture() { return texture; };
private:
	Texture * texture;
};

} // namespace gfx
