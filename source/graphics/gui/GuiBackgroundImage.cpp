#include "GuiBackgroundImage.h"

#include "Gui.h"
#include "graphics/Texture.h"
#include "graphics/device/Device.h"

namespace gfx
{

namespace gui
{

GuiBackgroundImage::GuiBackgroundImage(Gui & gui, GuiElement * parent,
		std::string const & imageName, Color backgroundColor, Color maskColor) :
	super(gui, parent),
	textureName(imageName),
	texture(gui.getDevice().grabTexture(gui.getModPath() + textureName)),
	backgroundColor(backgroundColor),
	maskColor(maskColor)
{}

GuiBackgroundImage::~GuiBackgroundImage()
{
	gui.getDevice().releaseTexture(gui.getModPath() + textureName);
}

void GuiBackgroundImage::draw()
{
	math::Vector2i screenSize = gui.getScreenSize();
	math::Vector2i imageSize(0, 0);
	if (texture != nullptr)
		imageSize = texture->getSize();

	math::Vector2i upperLeft = screenSize / 2 - imageSize / 2;
	math::Vector2i upperRight = upperLeft + imageSize;

	auto & device = gui.getDevice();

	device.draw2DRectangle(math::Recti(0, 0, screenSize.x, screenSize.y), backgroundColor);
	device.draw2DImage(texture, math::Recti(upperLeft, upperRight));
	device.draw2DRectangle(math::Recti(0, 0, screenSize.x, screenSize.y), maskColor);

	super::draw();
}

void GuiBackgroundImage::setMaskColor(Color color)
{
	maskColor = color;
}

} // namespace gui

} // namespace gfx
