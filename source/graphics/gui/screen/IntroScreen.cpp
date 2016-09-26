#include "IntroScreen.h"

#include <cstdint>
#include <iostream>

#include "../Gui.h"
#include "../GuiBackgroundImage.h"
#include "../../device/Device.h"

#include "engine/Engine.h"
#include "input/Input.h"

namespace gfx
{

namespace gui
{

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
	inputHandler(new InputHandler(input, *this)),
	introImage(nullptr),
	fadeColor(0, 0, 0),
	maxShowTime(3.0f),
	fadeStart(0.80f),
	showTime(0.0f)
{}

IntroScreen::~IntroScreen()
{}

void IntroScreen::create()
{
	std::cout << "Creating intro screen" << std::endl;

	showTime = 0.0f;

	device::Device* device = gui.getDevice();

	math::Vector2u screenSize = gui.getScreenSize();

	Texture* texture =
		(device != nullptr) ?
			device->loadTextureFromFile(gui.getModPath() + "sys/gfx/logo.bmp") :
			nullptr;

	introImage = gui.addBackgroundImage(texture);

	inputHandler->init();

	super::create();
}

void IntroScreen::destroy()
{
	std::cout << "Destroying intro screen" << std::endl;

	gui.deleteGuiElement(introImage);
	introImage = nullptr;

	inputHandler->remove();

	super::destroy();
}

void IntroScreen::update(float deltaTime)
{
	showTime += deltaTime;
	if (showTime > maxShowTime)
	{
		skipIntro();
	}
	else
	{
		float fadeStartTime = maxShowTime * fadeStart;
		if (showTime > fadeStartTime)
		{
			float fadeLength = maxShowTime - fadeStartTime;
			float fade = (showTime - fadeStartTime) / fadeLength;

			fadeColor.setAlpha(static_cast<uint8_t>(255.0f * fade));
			introImage->setMaskColor(fadeColor);
		}
	}

	super::update(deltaTime);
}

void IntroScreen::skipIntro()
{
	std::cout << "Skip intro!" << std::endl;

	Engine* engine = gui.getEngine();

	if (engine != nullptr)
	{
		engine->skipIntro();
	}
}

} // namespace gui

} // namespace gfx
