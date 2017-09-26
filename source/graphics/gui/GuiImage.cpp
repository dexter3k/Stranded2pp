#include "GuiImage.h"

#include "Gui.h"
#include "../Texture.h"
#include "../device/Device.h"

namespace gfx
{

namespace gui
{

GuiImage::GuiImage(Gui & gui, GuiElement * parent, std::string const & imageName,
		math::Vector2i position, bool centered) :
	super(gui, parent, position),
	textureName(imageName),
	texture(gui.getDevice().grabTexture(gui.getModPath() + textureName)),
	centered(centered)
{}

GuiImage::~GuiImage()
{
	gui.getDevice().releaseTexture(gui.getModPath() + textureName);
}

void GuiImage::draw()
{
	auto & device = gui.getDevice();

	auto position = getPosition();
	if (centered && texture != nullptr) {
		auto textureSize = texture->getSize();
		position -= textureSize / 2;
	}

	device.draw2DImage(texture, position);
}

} // namespace gui

} // namespace gfx
