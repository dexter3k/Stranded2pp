#include "Texture.h"

#include <iostream>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION 1
#endif // __APPLE__
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

	// TODO: MipMaps

	uploadTexture(true, 0, image.getRawData());

	// TODO: GL_NEAREST vs. GL_LINEAR. Which is in original game?
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	device.bindTexture(0, bindedTexture);
}

Texture::~Texture()
{
	if (glTextureName != 0)
	{
		glDeleteTextures(1, &glTextureName);
	}
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


	if (initTexture)
	{
		glTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(mipMapLevel), GL_RGBA,
			static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, static_cast<const GLvoid*>(data));
	}

	// TODO
}

} // namespace gfx
