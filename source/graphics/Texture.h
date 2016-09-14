#pragma once

#include <string>

#include "common/math/Vector2.h"

namespace gfx
{

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	const std::string& getName() const;

	const math::Vector2i& getOriginalSize() const;
	const math::Vector2i& getSize() const;

	bool hasAlpha() const;
	bool hasMipMaps() const;
	bool isRenderTarget() const;
private:
	std::string name;
	math::Vector2i originalSize;
};

} // namespace gfx
