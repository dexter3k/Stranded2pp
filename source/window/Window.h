#pragma once

#include <memory>

#include <SFML/Window.hpp>

class Input;
class Modification;

class Window
{
public:
	Window();
	~Window();

	bool init(const std::shared_ptr<const Modification>& modification);

	void display();

	void pollEvents();

	// Ignore config value and force start in windowed mode?
	void startInWindowedMode(bool value);

	void registerInput(const std::shared_ptr<Input>& input);
private:
	sf::Window window;

	bool shouldStartInWindowedMode;

	std::shared_ptr<Input> input;
};
