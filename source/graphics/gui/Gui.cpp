#include "Gui.h"

#include <cassert>
#include <iostream>

#include "screen/IntroScreen.h"
#include "screen/MainMenuScreen.h"

#include "common/Modification.h"
#include "input/Input.h"

#include "../device/Device.h"

#include "GuiBackgroundImage.h"
#include "GuiButton.h"
#include "GuiElement.h"
#include "GuiImage.h"

namespace gfx
{

namespace gui
{

Gui::InputHandler::InputHandler(Input& input, Gui& gui) :
	super(&input),
	gui(gui)
{}

bool Gui::InputHandler::onMouseButtonPressed(uint8_t button, int x, int y)
{
	gui.onMouseButtonPressed(button, x, y);

	return false;
}

bool Gui::InputHandler::onMouseMoved(int x, int y)
{
	gui.onMouseMoved(x, y);

	return false;
}

Gui::Gui(Input& input, device::Device* device) :
	RootElement(nullptr, this),
	inputHandler(input, *this),
	device(device),
	engine(nullptr),
	currentScreen(nullptr),
	introScreen(new IntroScreen(*this, input)),
	mainMenuScreen(new MainMenuScreen(*this, input)),
	guiElements(),
	modPath(""),
	screenSize(800, 600)
{}

Gui::~Gui()
{
	inputHandler.detach();

	if (currentScreen != nullptr)
	{
		currentScreen->destroy();
	}

	for (auto&& element : guiElements)
	{
		delete element;
	}
}

bool Gui::init(const Modification& modification)
{
	modPath = modification.getPath();

	screenSize = device->getRenderTargetSize();

	inputHandler.attach();

	return true;
}

void Gui::update(double deltaTime)
{
	screenSize = device->getRenderTargetSize();

	for (auto&& element : guiElements)
	{
		element->onAnimate(deltaTime);
	}

	if (currentScreen != nullptr)
	{
		currentScreen->update(deltaTime);
	}
}

void Gui::drawAll()
{
	RootElement::onDraw();
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

GuiElement* Gui::getRootElement()
{
	return this;
}

GuiButton* Gui::addButton(Texture* normalTexture, Texture* hoverTexture,
	const math::Vector2i& position, const math::Recti& sourceRectangle,
	GuiElement* parent, int id)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	GuiButton* button = new GuiButton(normalTexture, hoverTexture, position,
		sourceRectangle, parent, this, id);

	guiElements.push_back(button);

	return button;
}

GuiBackgroundImage* Gui::addBackgroundImage(Texture* texture,
	const Color& backgroundColor, const Color& maskColor,
	const math::Recti& sourceRectangle, GuiElement* parent, int id)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	GuiBackgroundImage* image = new GuiBackgroundImage(parent, this, texture,
		backgroundColor, maskColor, sourceRectangle, id);

	guiElements.push_back(image);

	return image;
}

GuiImage* Gui::addImage(Texture* texture,
	const math::Recti& destinationRectangle, const math::Recti& sourceRectangle,
	GuiElement* parent, int id)
{
	if (parent == nullptr)
	{
		parent = this;
	}

	GuiImage* image = new GuiImage(texture, destinationRectangle,
		sourceRectangle, parent, this, id);

	guiElements.push_back(image);

	return image;
}

void Gui::deleteGuiElement(GuiElement* element)
{
	assert(element != nullptr);

	auto end = guiElements.end();
	for (auto it = guiElements.begin(); it != end; ++it)
	{
		if ((*it) == element)
		{
			delete *it;

			guiElements.erase(it);

			return;
		}
	}
}

void Gui::connectEngine(Engine* engine)
{
	assert(engine != nullptr);
	assert(this->engine == nullptr);

	this->engine = engine;
}

const math::Vector2u& Gui::getScreenSize() const
{
	return screenSize;
}

Engine* Gui::getEngine() const
{
	return engine;
}

device::Device* Gui::getDevice() const
{
	return device;
}

const std::string& Gui::getModPath() const
{
	return modPath;
}

} // namespace gui

} // namespace gfx
