#include "MainMenuScreen.h"

#include "../Gui.h"
#include "../GuiButton.h"

#include "graphics/device/Device.h"
#include "input/Input.h"

namespace gfx
{

namespace gui
{

MainMenuScreen::MainMenuScreen(Gui& gui, Input&) :
	super(gui),
	testButton(nullptr)
{}

MainMenuScreen::~MainMenuScreen()
{}

void MainMenuScreen::create()
{
	super::create();

	device::Device* device = gui.getDevice();
	if (device != nullptr)
	{
		testButton = gui.addButton(
			device->grabTexture(gui.getModPath() + "sys/gfx/bigbutton.bmp"),
			device->grabTexture(
				gui.getModPath() + "sys/gfx/bigbutton_over.bmp"),
			math::Vector2i(50, 50));
	}
}

void MainMenuScreen::destroy()
{
	if (testButton != nullptr)
	{
		gui.deleteGuiElement(testButton);
		testButton = nullptr;
	}

	device::Device* device = gui.getDevice();
	if (device != nullptr)
	{
		device->releaseTexture(gui.getModPath() + "sys/gfx/bigbutton.bmp");
		device->releaseTexture(gui.getModPath() + "sys/gfx/bigbutton_over.bmp");
	}

	super::destroy();
}

void MainMenuScreen::update(double deltaTime)
{
	super::update(deltaTime);
}

} // namespace gui

} // namespace gfx
