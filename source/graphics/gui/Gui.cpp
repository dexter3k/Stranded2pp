#include "Gui.h"

#include "screen/IntroScreen.h"
#include "screen/MainMenuScreen.h"

#include "common/Modification.h"
#include "input/Input.h"

namespace gfx
{

namespace gui
{

Gui::Gui(Input& input, device::Device* device) :
	input(input),
	currentScreen(nullptr),
	introScreen(new IntroScreen(*this, input)),
	mainMenuScreen(new MainMenuScreen(*this, input))
{}

Gui::~Gui()
{
	if (currentScreen != nullptr)
	{
		currentScreen->destroy();
	}
}

bool Gui::init(const Modification& modification)
{
	setScreen(Screen::Intro);

	return true;
}

void Gui::update(float deltaTime)
{
	if (currentScreen != nullptr)
	{
		currentScreen->update(deltaTime);
	}
}

void Gui::drawAll()
{
	
}

void Gui::setScreen(Screen::Screens screen)
{
	if (currentScreen != nullptr)
	{
		currentScreen->destroy();
	}

	switch (screen)
	{
		case Screen::Intro:
		{
			currentScreen = introScreen.get();

			break;
		}
		case Screen::MainMenu:
		{
			currentScreen = mainMenuScreen.get();

			break;
		}
		default:
		{
			currentScreen = nullptr;

			break;
		}
	}

	if (currentScreen != nullptr)
	{
		currentScreen->create();
	}
}

} // namespace gui

} // namespace gfx
