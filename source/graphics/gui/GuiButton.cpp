#include "GuiButton.h"

#include <iostream>

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
	super(parent, gui, id, position),
	textures{normalTexture, hoverTexture},
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

void GuiButton::onDraw()
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

bool GuiButton::onMouseButtonPressed(uint8_t button, int x, int y)
{
	if (isVisible)
	{
		math::Vector2i lowerRight =
			position + sourceRectangle.lowerRight - sourceRectangle.upperLeft;

		if (x > position.x && y > position.y &&
			x < lowerRight.x && y < lowerRight.y)
		{
			std::cout << "Pressed!" << std::endl;
		}
	}

	return super::onMouseButtonPressed(button, x, y);
}

bool GuiButton::onMouseMoved(int x, int y)
{
	if (isVisible)
	{
		math::Vector2i lowerRight =
			position + sourceRectangle.lowerRight - sourceRectangle.upperLeft;

		if (x > position.x && y > position.y &&
			x < lowerRight.x && y < lowerRight.y)
		{
			isHovered = true;
		}
		else
		{
			isHovered = false;
		}
	}

	return super::onMouseMoved(x, y);
}

} // namespace gui

} // namespace gfx
