#include "IntroScreen.h"

#include <iostream>

#include "../Gui.h"

#include "input/Input.h"

bool IntroScreen::InputHandler::onKeyPressed(uint8_t key, bool alt,
	bool control, bool shift, bool super)
{
	introScreen.skipIntro();

	return false;
}

bool IntroScreen::InputHandler::onMouseButtonPressed(uint8_t button, int x,
	int y)
{
	introScreen.skipIntro();

	return false;
}

IntroScreen::IntroScreen(Gui& gui, Input& input) :
	super(gui),
	inputHandler(new InputHandler(input, *this))
{}

IntroScreen::~IntroScreen()
{}

void IntroScreen::create()
{
	super::create();

	inputHandler->init();

	std::cout << "Creating intro screen" << std::endl;
}

void IntroScreen::destroy()
{
	std::cout << "Destroying intro screen" << std::endl;

	inputHandler->remove();

	super::destroy();
}

void IntroScreen::update(float deltaTime)
{
	super::update(deltaTime);
}

void IntroScreen::skipIntro()
{
	std::cout << "Skip intro!" << std::endl;

	gui.setScreen(Screen::MainMenu);
}
