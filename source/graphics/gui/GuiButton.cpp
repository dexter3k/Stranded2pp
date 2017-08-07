#include "GuiButton.h"

#include <iostream>

#include "Gui.h"
#include "../Texture.h"
#include "../device/Device.h"

namespace gfx
{

namespace gui
{

unsigned const GuiButton::width = 190;
unsigned const GuiButton::height = 45;

std::string const GuiButton::textureName = "sys/gfx/bigbutton.bmp";
std::string const GuiButton::textureHoveredName = "sys/gfx/bigbutton_over.bmp";

GuiButton::GuiButton(Gui & gui, GuiElement * parent, math::Vector2i position,
		std::string const &, FontType, std::function<void(void)> onPressed) :
	super(gui, parent, position),
	texture(gui.getDevice().grabTexture(gui.getModPath() + textureName)),
	textureHovered(gui.getDevice().grabTexture(gui.getModPath() + textureHoveredName)),
	isHovered(false),
	onPressed(onPressed)
{}

GuiButton::~GuiButton()
{
	gui.getDevice().releaseTexture(gui.getModPath() + textureName);
	gui.getDevice().releaseTexture(gui.getModPath() + textureHoveredName);
}

void GuiButton::draw()
{
	auto & device = gui.getDevice();

	device.draw2DImage(isHovered ? textureHovered : texture, getPosition());
}

bool GuiButton::onMouseButtonPressed(uint8_t button, int x, int y)
{
	if (!isVisible())
		return false;

	math::Vector2i lowerRight = getPosition() + math::Vector2i(width, height);

	bool pressed = (x > getPosition().x && y > getPosition().y && x < lowerRight.x && y < lowerRight.y);
	if (pressed && onPressed != nullptr)
		onPressed();

	return super::onMouseButtonPressed(button, x, y);
}

bool GuiButton::onMouseMoved(int x, int y)
{
	if (!isVisible())
		return false;

	math::Vector2i lowerRight = getPosition() + math::Vector2i(width, height);

	isHovered = (x > getPosition().x && y > getPosition().y && x < lowerRight.x && y < lowerRight.y);

	return super::onMouseMoved(x, y);
}

} // namespace gui

} // namespace gfx
