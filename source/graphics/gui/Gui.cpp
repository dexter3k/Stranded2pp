#include "Gui.h"

#include <cassert>
#include <iostream>

#include "GuiBackgroundImage.h"
#include "GuiButton.h"
#include "GuiElement.h"
#include "GuiImage.h"
#include "GuiWindow.h"

#include "common/Modification.h"
#include "graphics/device/Device.h"

namespace gfx
{

namespace gui
{

Gui::Gui(device::Device & device, Modification const & modification) :
	RootElement(*this, nullptr),
	modPath(modification.getPath()),
	device(device),
	textEngine(device, modification),
	screenSize(device.getRenderTargetSize()),
	guiElements(),
	lastMousePosition(0, 0)
{}

Gui::~Gui()
{
	for (auto element : guiElements)
		delete element;
}

bool Gui::processEvent(Event event)
{
	switch (event.type) {
	case Event::MouseMoved:
		lastMousePosition = math::Vector2i(event.mouseMoved.x, event.mouseMoved.y);
		return RootElement::onMouseMoved(lastMousePosition.x, lastMousePosition.y);
	case Event::MouseButtonPressed:
		return RootElement::onMouseButtonPressed(event.mouseButtonPressed.button,
			event.mouseButtonPressed.x, event.mouseButtonPressed.y);
	case Event::MouseButtonReleased:
		return RootElement::onMouseButtonReleased(event.mouseButtonReleased.button,
			event.mouseButtonReleased.x, event.mouseButtonReleased.y);
	default:
		return false;
	}
}

void Gui::update(double deltaTime)
{
	RootElement::animate(deltaTime);
}

void Gui::drawAll()
{
	RootElement::draw();
}

GuiElement * Gui::createEmptyElement(GuiElement * parent)
{
	if (parent == nullptr)
		parent = this;

	GuiElement * element = new GuiElement(*this, parent);

	guiElements.push_back(element);

	return element;
}

GuiButton * Gui::createButton(math::Vector2i position, std::string const & text,
	FontType font, std::function<void(void)> onPressed, GuiElement * parent)
{
	if (parent == nullptr)
		parent = this;

	GuiButton * button = new GuiButton(*this, parent, position, text, font, onPressed);

	guiElements.push_back(button);

	return button;
}

GuiBackgroundImage * Gui::createBackgroundImage(std::string const & imageName,
	Color backgroundColor, Color maskColor, GuiElement * parent)
{
	if (parent == nullptr)
		parent = this;

	GuiBackgroundImage * image = new GuiBackgroundImage(*this, parent, imageName,
		backgroundColor, maskColor);

	guiElements.push_back(image);

	return image;
}

GuiWindow * Gui::createWindow(int position, std::string const & title, GuiElement * parent)
{
	if (parent == nullptr)
		parent = this;

	GuiWindow * window = new GuiWindow(*this, parent, position, title);

	guiElements.push_back(window);

	return window;
}

GuiImage * Gui::createImage(std::string const & imageName, math::Vector2i position,
	bool centered, GuiElement * parent)
{
	if (parent == nullptr)
		parent = this;

	GuiImage * image = new GuiImage(*this, parent, imageName, position, centered);

	guiElements.push_back(image);

	return image;
}

void Gui::deleteGuiElement(GuiElement * element)
{
	assert(element != nullptr);

	auto end = guiElements.end();
	for (auto it = guiElements.begin(); it != end; ++it) {
		if ((*it) == element) {
			delete *it;

			guiElements.erase(it);

			return;
		}
	}
}

} // namespace gui

} // namespace gfx
