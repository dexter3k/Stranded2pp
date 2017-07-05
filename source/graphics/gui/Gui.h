#pragma once

#include <list>
#include <memory>
#include <string>

#include "screen/Screen.h"
#include "../Color.h"
#include "common/math/Rect.h"

#include "GuiElement.h"

class Engine;
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
class IntroScreen;
class MainMenuScreen;

class Gui : public GuiElement
{
	typedef GuiElement RootElement;
public:
	Gui(Input& input, device::Device* device);
	~Gui();

	bool init(const Modification& modification);
	void update(double deltaTime);

	void drawAll();

	void setScreen(Screen::Screens screen);

	GuiElement* getRootElement();

	GuiButton* addButton(Texture* normalTexture, Texture* hoverTexture,
		const math::Vector2i& position,
		const math::Recti& sourceRectangle = math::Recti(0, 0, 0, 0),
		GuiElement* parent = nullptr, int id = -1);

	GuiBackgroundImage* addBackgroundImage(Texture* texture,
		const Color& backgroundColor = Color(0, 0, 0),
		const Color& maskColor = Color(0, 0, 0, 0),
		const math::Recti& sourceRectangle = math::Recti(0, 0, 0, 0),
		GuiElement* parent = nullptr, int id = -1);

	GuiImage* addImage(Texture* texture,
		const math::Recti& destinationRectangle,
		const math::Recti& sourceRectangle = math::Recti(0, 0, 0, 0),
		GuiElement* parent = nullptr, int id = -1);

	void deleteGuiElement(GuiElement* element);

	void connectEngine(Engine* engine);

	const math::Vector2u& getScreenSize() const;

	Engine* getEngine() const;
	device::Device* getDevice() const;
	const std::string& getModPath() const;
private:
	device::Device* device;
	Engine* engine;

	Screen* currentScreen;
	std::shared_ptr<IntroScreen> introScreen;
	std::shared_ptr<MainMenuScreen> mainMenuScreen;

	std::list<GuiElement*> guiElements;

	std::string modPath;

	math::Vector2u screenSize;
};

} // namespace gui

} // namespace gfx
