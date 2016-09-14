#pragma once

#include <string>

#include <SFML/OpenGL.hpp>

#include "Image.h"

#include "common/math/Vector2.h"

namespace gfx
{

namespace device
{
	class OpenGLDevice;
}

class Texture
{
public:
	Texture(const std::string& name, const Image& image,
		device::OpenGLDevice& device);
	~Texture();

	const std::string& getName() const;

	const math::Vector2u& getSize() const;

	GLuint getGlTextureName() const;
private:
	void uploadTexture(bool initTexture, unsigned mipMapLevel,
		const void* data);
private:
	std::string name;

	math::Vector2u size;

	GLuint glTextureName;
};

} // namespace gfx
