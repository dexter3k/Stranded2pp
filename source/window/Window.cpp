#include "Window.h"

#include <cassert>
#include <iostream>

#include "common/Modification.h"
#include "input/Input.h"

Window::Window() :
	window(),
	shouldStartInWindowedMode(false),
	input(nullptr)
{}

Window::~Window()
{}

bool Window::init(const std::shared_ptr<const Modification>& modification)
{
	auto& gameSettings = modification->getSettings();

	// GL context settings
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 0;
	contextSettings.antialiasingLevel = 0;
	contextSettings.majorVersion = 2;
	contextSettings.minorVersion = 1;

	// Video mode
	sf::VideoMode videoMode;
	videoMode.width = gameSettings.screen.width;
	videoMode.height = gameSettings.screen.height;
	videoMode.bitsPerPixel = gameSettings.screen.bitsPerPixel;

	// Check fullscreen video mode
	if (!shouldStartInWindowedMode && !videoMode.isValid())
	{
		std::cout << "Error: invalid video mode! Selecting default..." <<
			std::endl;

		auto modes = sf::VideoMode::getFullscreenModes();
		videoMode = modes[0]; // Best available
	}

	std::string title = "S2++ '";
	title += modification->getName() + "' mod";

	// Create window
	window.create(videoMode, title,
		(shouldStartInWindowedMode ?
			(sf::Style::Titlebar | sf::Style::Close) :
			sf::Style::Fullscreen),
		contextSettings);
	window.setActive();

	// Set FPS limit or VSync
	if (false)
	{
		window.setVerticalSyncEnabled(true);
	}
	else
	{
		window.setFramerateLimit(60);
	}

	return true;
}

void Window::display()
{
	window.display();
}

void Window::pollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: input->onRawEventClosed();
			default: continue;
		}
	}
}

void Window::startInWindowedMode(bool value)
{
	shouldStartInWindowedMode = value;
}

void Window::registerInput(const std::shared_ptr<Input>& input)
{
	assert(this->input.get() == nullptr);
	
	this->input = input;
}
