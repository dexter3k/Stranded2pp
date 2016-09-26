#include "GuiBackgroundImage.h"

#include "Gui.h"
#include "../Texture.h"
#include "../device/Device.h"

namespace gfx
{

namespace gui
{

GuiBackgroundImage::GuiBackgroundImage(GuiElement* parent, Gui* gui,
		Texture* backgroundTexture, const Color& backgroundColor,
		const Color& maskColor, bool stretched,
		const math::Recti& sourceRectangle, int id) :
	super(parent, gui, id),
	texture(backgroundTexture),
	destinationRectangle(),
	sourceRectangle(sourceRectangle),
	backgroundColor(backgroundColor),
	maskColor(maskColor),
	isStretched(stretched)
{
	if (sourceRectangle.upperLeft.x == 0 &&
		sourceRectangle.upperLeft.y == 0 &&
		sourceRectangle.lowerRight.x == 0 &&
		sourceRectangle.lowerRight.y == 0)
	{
		if (texture != nullptr)
		{
			this->sourceRectangle.lowerRight = texture->getSize();
		}
	}

	math::Vector2i imageSize =
		this->sourceRectangle.lowerRight - this->sourceRectangle.upperLeft;
	math::Vector2u screenSize = gui->getScreenSize();

	destinationRectangle.upperLeft.x = screenSize.x / 2 - imageSize.x / 2;
	destinationRectangle.upperLeft.y = screenSize.y / 2 - imageSize.y / 2;
	destinationRectangle.lowerRight =
		destinationRectangle.upperLeft + imageSize;
}

GuiBackgroundImage::~GuiBackgroundImage()
{}

void GuiBackgroundImage::draw()
{
	device::Device* device = gui->getDevice();

	if (device != nullptr)
	{
		math::Vector2u screenSize = gui->getScreenSize();

		device->draw2DRectangle(math::Recti(0, 0, screenSize.x, screenSize.y),
			backgroundColor);
		device->draw2DImage(texture, destinationRectangle, sourceRectangle);

		if (maskColor.getAlpha() > 0)
		{
			device->draw2DRectangle(
				math::Recti(0, 0, screenSize.x, screenSize.y),
				maskColor);
		}
	}
}

void GuiBackgroundImage::setMaskColor(const Color& color)
{
	maskColor = color;
}

} // namespace gui

} // namespace gfx
