#pragma once

#include <memory>

#include <SFML/Window.hpp>

class Modification;

class Window
{
public:
	Window();
	~Window();

	bool init(const std::shared_ptr<const Modification>& modification);

	// Ignore config value and force start in windowed mode?
	void startInWindowedMode(bool value);
private:
	sf::Window window;

	bool shouldStartInWindowedMode;
};
