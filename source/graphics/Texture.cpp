#include "Texture.h"

namespace gfx
{

Texture::Texture(const std::string& path) :
	originalSize(0, 0)
{}

Texture::~Texture()
{}

const math::Vector2i& Texture::getOriginalSize() const
{
	return originalSize;
}

} // namespace gfx
