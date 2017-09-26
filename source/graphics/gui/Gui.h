#pragma once

#include <functional>
#include <list>
#include <string>

#include "GuiElement.h"

#include "graphics/Color.h"
#include "graphics/TextEngine.h"
#include "graphics/FontType.h"
#include "input/Event.h"
#include "math/Rect.h"

class Input;
class Modification;

namespace gfx
{

class Texture;

namespace device
{
	class Device;
}

namespace gui
{

class GuiBackgroundImage;
class GuiButton;
class GuiImage;
class GuiWindow;

class Gui : public GuiElement
{
	typedef GuiElement RootElement;
public:
	Gui(device::Device & device, Modification const & modification);
	~Gui();

	bool processEvent(Event event);
	void update(double deltaTime);

	void drawAll();

	GuiElement * createEmptyElement(GuiElement * parent = nullptr);

	GuiButton * createButton(math::Vector2i position, std::string const & text,
		FontType font, std::function<void(void)> onPressed = nullptr, GuiElement * parent = nullptr);

	GuiBackgroundImage * createBackgroundImage(std::string const & imageName,
		Color backgroundColor = Color(0, 0, 0), Color maskColor = Color(0, 0, 0, 0),
		GuiElement * parent = nullptr);

	GuiWindow * createWindow(int position, std::string const & title, GuiElement * parent = nullptr);

	GuiImage * createImage(std::string const & imageName, math::Vector2i position,
		bool centered = false, GuiElement * parent = nullptr);

	void deleteGuiElement(GuiElement * element);

	math::Vector2i getMousePosition() const { return lastMousePosition; };

	std::string const & getModPath() const { return modPath; };

	device::Device & getDevice() const { return device; };

	TextEngine & getTextEngine() { return textEngine; };

	math::Vector2u getScreenSize() const { return screenSize; };
private:
	std::string modPath;

	device::Device & device;

	TextEngine textEngine;

	math::Vector2u screenSize;

	std::list<GuiElement*> guiElements;

	math::Vector2i lastMousePosition;
};

} // namespace gui

} // namespace gfx
