#pragma once

#include <memory>

#include <SFML/Window.hpp>

class Input;
class Modification;

class Window
{
public:
	Window(bool forceWindowedMode);

	bool init(const Modification& modification);

	void display();

	void pollEvents();

	// Ignore config value and force start in windowed mode?
	void startInWindowedMode(bool value);

	void registerInput(Input* input);
private:
	sf::Window window;

	bool shouldStartInWindowedMode;

	Input* input;
};
