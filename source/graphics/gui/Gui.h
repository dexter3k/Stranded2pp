#pragma once

#include <memory>

#include "screen/Screen.h"

class Input;
class Modification;

namespace gfx
{

namespace device
{
	class Device;
}

namespace gui
{

class IntroScreen;
class MainMenuScreen;

class Gui
{
public:
	Gui(Input& input, device::Device* device);
	~Gui();

	bool init(const Modification& modification);
	void update(float deltaTime);

	void drawAll();

	void setScreen(Screen::Screens screen);
private:
	Input& input;

	Screen* currentScreen;
	std::shared_ptr<IntroScreen> introScreen;
	std::shared_ptr<MainMenuScreen> mainMenuScreen;
};

} // namespace gui

} // namespace gfx
