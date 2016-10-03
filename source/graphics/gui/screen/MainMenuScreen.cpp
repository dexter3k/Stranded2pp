#include "MainMenuScreen.h"

#include <iostream>

#include "../Gui.h"
#include "../GuiButton.h"
#include "../../device/Device.h"

#include "input/Input.h"

namespace gfx
{

namespace gui
{

bool MainMenuScreen::InputHandler::onMouseButtonPressed(uint8_t button, int x,
	int y)
{
	return false;
}

bool MainMenuScreen::InputHandler::onMouseMoved(int x, int y)
{
	return false;
}

MainMenuScreen::MainMenuScreen(Gui& gui, Input& input) :
	super(gui),
	inputHandler(new InputHandler(input, *this)),
	button1(nullptr)
{}

MainMenuScreen::~MainMenuScreen()
{}

void MainMenuScreen::create()
{
	std::cout << "Creating main menu screen" << std::endl;

	device::Device* device = gui.getDevice();

	math::Vector2u screenSize = gui.getScreenSize();

	Texture* textures[] = {nullptr, nullptr};
	if (device != nullptr)
	{
		textures[0] = device->loadTextureFromFile(
			gui.getModPath() + "sys/gfx/bigbutton.bmp", false, true);
		textures[1] = device->loadTextureFromFile(
			gui.getModPath() + "sys/gfx/bigbutton_over.bmp", false, true);
	}

	button1 = gui.addButton(textures[0], textures[1], math::Vector2i(50, 50));

	gui.addImage(device->loadTextureFromFile(gui.getModPath() + "sys/gfx/wrenchItem.png"), math::Recti(100, 100, 500, 500));

	inputHandler->init();

	super::create();
}

void MainMenuScreen::destroy()
{
	std::cout << "Destroying main menu screen" << std::endl;

	gui.deleteGuiElement(button1);
	button1 = nullptr;

	inputHandler->remove();

	super::destroy();
}

void MainMenuScreen::update(float deltaTime)
{
	super::update(deltaTime);
}

} // namespace gui

} // namespace gfx
