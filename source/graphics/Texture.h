#pragma once

#include <string>

#include <SFML/OpenGL.hpp>

#include "Image.h"

#include "math/Vector2.h"

namespace gfx
{

namespace device
{
	class OpenGLDevice;
}

// TODO
// WTF, this should really be OpenGLTexture
class Texture
{
public:
	Texture(std::string const & name, Image const & image, device::OpenGLDevice & device);
	~Texture();

	std::string const & getName() const { return name; };

	math::Vector2u getSize() const { return size; };

	GLuint getGlTextureName() const;
private:
	void uploadTexture(bool initTexture, unsigned mipMapLevel, void const * data);
private:
	std::string name;

	math::Vector2u size;

	GLuint glTextureName;
};

} // namespace gfx
