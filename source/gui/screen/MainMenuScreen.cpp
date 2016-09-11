#include "MainMenuScreen.h"

#include <iostream>

#include "../Gui.h"

#include "input/Input.h"

bool MainMenuScreen::InputHandler::onMouseButtonPressed(uint8_t button, int x,
	int y)
{
	return false;
}

MainMenuScreen::MainMenuScreen(Gui& gui, Input& input) :
	super(gui),
	inputHandler(new InputHandler(input, *this))
{}

MainMenuScreen::~MainMenuScreen()
{}

void MainMenuScreen::create()
{
	super::create();

	inputHandler->init();

	std::cout << "Creating main menu screen" << std::endl;
}

void MainMenuScreen::destroy()
{
	std::cout << "Destroying main menu screen" << std::endl;

	inputHandler->remove();

	super::destroy();
}

void MainMenuScreen::update(float deltaTime)
{
	super::update(deltaTime);
}
