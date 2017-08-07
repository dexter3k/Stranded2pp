#include "GuiImage.h"

#include "Gui.h"
#include "../Texture.h"
#include "../device/Device.h"

namespace gfx
{

namespace gui
{

GuiImage::GuiImage(Gui & gui, GuiElement * parent, Texture * texture, math::Recti const & destinationRectangle,
		const math::Recti& sourceRectangle) :
	super(gui, parent),
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

void GuiImage::draw()
{
	auto & device = gui.getDevice();

	device.draw2DImage(texture, destinationRectangle, sourceRectangle);
}

} // namespace gui

} // namespace gfx
