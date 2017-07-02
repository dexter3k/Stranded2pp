#include "MainMenuScreen.h"

#include "../Gui.h"
#include "../GuiButton.h"

#include "graphics/device/Device.h"
#include "input/Input.h"

namespace gfx
{

namespace gui
{

MainMenuScreen::InputHandler::InputHandler(Input& input,
		MainMenuScreen& mainMenuScreen) :
	super(&input),
	mainMenuScreen(mainMenuScreen)
{}

bool MainMenuScreen::InputHandler::onMouseButtonPressed(uint8_t, int, int)
{
	return false;
}

MainMenuScreen::MainMenuScreen(Gui& gui, Input& input) :
	super(gui),
	inputHandler(new InputHandler(input, *this)),
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

	inputHandler->init();
}

void MainMenuScreen::destroy()
{
	inputHandler->remove();

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
