#include "Texture.h"

#include <iostream>

#include "device/OpenGLDevice.h"

namespace gfx
{

Texture::Texture(const std::string& name, const Image& image,
		device::OpenGLDevice& device) :
	name(name),
	size(0),
	glTextureName(0)
{
	size = image.getSize();

	if (size.x == 0 || size.y == 0)
	{
		std::cout << "Invalid size of image for texture: x: " << size.x << " y:"
			<< size.y << std::endl;
		return;
	}

	glGenTextures(1, &glTextureName);

	Texture* bindedTexture = device.getBindedTexture(0);
	device.bindTexture(0, this);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// TODO: MipMaps

	uploadTexture(true, 0, image.getRawData());

	device.bindTexture(0, bindedTexture);
}

Texture::~Texture()
{
	if (glTextureName != 0)
	{
		glDeleteTextures(1, &glTextureName);
	}
}

const std::string& Texture::getName() const
{
	return name;
}

const math::Vector2u& Texture::getSize() const
{
	return size;
}

GLuint Texture::getGlTextureName() const
{
	return glTextureName;
}

void Texture::uploadTexture(bool initTexture, unsigned mipMapLevel,
	const void* data)
{
	if (!data)
	{
		return;
	}

	unsigned width = size.x >> mipMapLevel;
	unsigned height = size.y >> mipMapLevel;


	glTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(mipMapLevel), GL_RGBA,
		static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA,
		GL_UNSIGNED_BYTE, static_cast<const GLvoid*>(data));
}

} // namespace gfx
