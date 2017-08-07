#pragma once

#include <functional>
#include <list>
#include <string>

#include "GuiElement.h"

#include "graphics/Color.h"
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

	GuiButton * createButton(math::Vector2i const & position, std::string const & text,
		FontType font, std::function<void(void)> onPressed = nullptr, GuiElement * parent = nullptr);

	GuiBackgroundImage * addBackgroundImage(std::string const & imageName,
		Color backgroundColor = Color(0, 0, 0), Color maskColor = Color(0, 0, 0, 0),
		GuiElement * parent = nullptr);

	GuiImage* addImage(Texture * texture,
		const math::Recti& destinationRectangle,
		const math::Recti& sourceRectangle = math::Recti(0, 0, 0, 0),
		GuiElement * parent = nullptr);

	void deleteGuiElement(GuiElement * element);

	std::string const & getModPath() const { return modPath; };

	device::Device & getDevice() const { return device; };

	math::Vector2u getScreenSize() const { return screenSize; };
private:
	std::string modPath;

	device::Device & device;

	math::Vector2u screenSize;

	std::list<GuiElement*> guiElements;
};

} // namespace gui

} // namespace gfx
