#include "GuiWindow.h"

#include <iostream>

#include "Gui.h"
#include "graphics/Texture.h"
#include "graphics/device/Device.h"

namespace gfx
{

namespace gui
{

std::string const GuiWindow::backgroundImage = "sys/gfx/woodback_dark.bmp";

unsigned const GuiWindow::width = 580;
unsigned const GuiWindow::height = 595;

GuiWindow::GuiWindow(Gui & gui, GuiElement * parent, math::Vector2i position) :
	super(gui, parent, position),
	backgroundTexture(gui.getDevice().grabTexture(gui.getModPath() + backgroundImage))
{}

GuiWindow::~GuiWindow()
{
	gui.getDevice().releaseTexture(gui.getModPath() + backgroundImage);
}

void GuiWindow::draw()
{
	auto & device = gui.getDevice();

	device.draw2DImage(
		backgroundTexture,
		math::Recti(getPosition(), getPosition() + math::Vector2i(width, height)),
		math::Recti(math::Vector2i(0, 0), math::Vector2i(backgroundTexture->getSize())));
}

} // namespace gui

} // namespace gfx
