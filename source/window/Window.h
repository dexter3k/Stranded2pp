#pragma once

#include <memory>

#include <SFML/Window.hpp>

class Input;
class Modification;

class Window
{
public:
	Window(bool forceWindowedMode, Modification const & modification);

	void display();

	void pollEvents();

	void registerInput(Input* input);
private:
	bool init(bool forceWindowedMode, Modification const & modification);
private:
	sf::Window window;

	Input* input;
};
