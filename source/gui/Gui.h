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
	Gui(Input& input);
	~Gui();

	bool init(const Modification& modification);
	void update(float deltaTime);

	void setScreen(Screen::Screens screen);
private:
	Input& input;

	Screen* currentScreen;
	std::shared_ptr<IntroScreen> introScreen;
	std::shared_ptr<MainMenuScreen> mainMenuScreen;
};
