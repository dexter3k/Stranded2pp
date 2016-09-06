#pragma once

#include <memory>

#include "screen/Screen.h"

class Input;
class IntroScreen;
class MainMenuScreen;
class Modification;

class Gui
{
public:
	Gui(const std::shared_ptr<Input>& input);
	~Gui();

	bool init(const std::shared_ptr<const Modification>& modification);
	void update(float deltaTime);

	void setScreen(Screen::Screens screen);
private:
	std::shared_ptr<Input> input;

	Screen* currentScreen;
	std::shared_ptr<IntroScreen> introScreen;
	std::shared_ptr<MainMenuScreen> mainMenuScreen;
};
