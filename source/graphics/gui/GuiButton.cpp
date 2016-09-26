#include "GuiButton.h"

#include "Gui.h"
#include "../Texture.h"
#include "../device/Device.h"

namespace gfx
{

namespace gui
{

GuiButton::GuiButton(Texture* normalTexture, Texture* hoverTexture,
		const math::Vector2i& position, const math::Recti& sourceRectangle,
		GuiElement* parent, Gui* gui, int id) :
	super(parent, gui, id),
	textures{normalTexture, hoverTexture},
	position(position),
	sourceRectangle(sourceRectangle),
	isHovered(false)
{
	if (sourceRectangle.upperLeft.x == 0 &&
		sourceRectangle.upperLeft.y == 0 &&
		sourceRectangle.lowerRight.x == 0 &&
		sourceRectangle.lowerRight.y == 0)
	{
		if (normalTexture != nullptr)
		{
			this->sourceRectangle.lowerRight = normalTexture->getSize();
		}
		else if (hoverTexture != nullptr)
		{
			this->sourceRectangle.lowerRight = hoverTexture->getSize();
		}
	}
}

GuiButton::~GuiButton()
{}

void GuiButton::draw()
{
	device::Device* device = gui->getDevice();
	if (device != nullptr)
	{
		if (isHovered)
		{
			device->draw2DImage(textures[1], position, sourceRectangle);
		}
		else
		{
			device->draw2DImage(textures[0], position, sourceRectangle);
		}
	}
}

} // namespace gui

} // namespace gfx
