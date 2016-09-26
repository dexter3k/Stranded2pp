#include "GuiImage.h"

#include "Gui.h"
#include "../Texture.h"
#include "../device/Device.h"

namespace gfx
{

namespace gui
{

GuiImage::GuiImage(Texture* texture, const math::Recti& destinationRectangle,
		const math::Recti& sourceRectangle, GuiElement* parent, Gui* gui, int id) :
	super(parent, gui, id),
	texture(texture),
	destinationRectangle(destinationRectangle),
	sourceRectangle(sourceRectangle)
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
}

GuiImage::~GuiImage()
{}

void GuiImage::draw()
{
	device::Device* device = gui->getDevice();
	if (device != nullptr)
	{
		device->draw2DImage(texture, destinationRectangle, sourceRectangle);
	}
}

} // namespace gui

} // namespace gfx
