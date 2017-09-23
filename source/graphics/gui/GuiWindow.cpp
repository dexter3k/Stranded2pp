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
std::string const GuiWindow::borderCornerImage = "sys/gfx/border_corn.bmp";
std::string const GuiWindow::borderVerticalImage = "sys/gfx/border_vert.bmp";
std::string const GuiWindow::borderHorizontalImage = "sys/gfx/border_hori.bmp";

unsigned const GuiWindow::width = 580;
unsigned const GuiWindow::height = 595;

GuiWindow::GuiWindow(Gui & gui, GuiElement * parent, math::Vector2i position) :
	super(gui, parent, position),
	backgroundTexture(gui.getDevice().grabTexture(gui.getModPath() + backgroundImage)),
	borderCorner(gui.getDevice().grabTexture(gui.getModPath() + borderCornerImage)),
	borderVertical(gui.getDevice().grabTexture(gui.getModPath() + borderVerticalImage)),
	borderHorizontal(gui.getDevice().grabTexture(gui.getModPath() + borderHorizontalImage))
{}

GuiWindow::~GuiWindow()
{
	gui.getDevice().releaseTexture(gui.getModPath() + backgroundImage);
	gui.getDevice().releaseTexture(gui.getModPath() + borderCornerImage);
	gui.getDevice().releaseTexture(gui.getModPath() + borderVerticalImage);
	gui.getDevice().releaseTexture(gui.getModPath() + borderHorizontalImage);
}

void GuiWindow::draw()
{
	auto & device = gui.getDevice();

	// Cut 8 pixels from each side like in original game (why?)
	math::Recti clippingRectangle(
		getPosition() + math::Vector2i(8, 0),
		getPosition() + math::Vector2i(width - 8, height - 8));
	device.draw2DImage(
		backgroundTexture,
		math::Recti(getPosition(), getPosition() + math::Vector2i(width, height)),
		&clippingRectangle);
	device.draw2DImage(
		borderHorizontal,
		math::Recti(
			getPosition() + math::Vector2i(0, height - 16),
			getPosition() + math::Vector2i(width, height)));
	device.draw2DImage(
		borderVertical,
		math::Recti(
			getPosition(),
			getPosition() + math::Vector2i(16, height)));
	device.draw2DImage(
		borderVertical,
		math::Recti(
			getPosition() + math::Vector2i(width - 16, 0),
			getPosition() + math::Vector2i(width, height)));
	device.draw2DImage(
		borderCorner,
		math::Recti(
			getPosition() + math::Vector2i(0, height - 16),
			getPosition() + math::Vector2i(16, height)));
	device.draw2DImage(
		borderCorner,
		math::Recti(
			getPosition() + math::Vector2i(width - 16, height - 16),
			getPosition() + math::Vector2i(width, height)));
}

} // namespace gui

} // namespace gfx
