#include "Window.h"

#include <cassert>
#include <iostream>

#include "common/Modification.h"
#include "input/Input.h"
#include "input/Keyboard.h"

Window::Window() :
	window(),
	shouldStartInWindowedMode(false),
	input(nullptr)
{}

Window::~Window()
{}

bool Window::init(const Modification& modification)
{
	auto& gameSettings = modification.getSettings();

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
	title += modification.getName() + "' mod";

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
		window.setFramerateLimit(30);
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
			case sf::Event::Closed:
			{
				input->onRawEventClosed();
				break;
			}
			case sf::Event::Resized:
			{
				input->onRawEventResized(event.size.width, event.size.height);
				break;
			}
			case sf::Event::LostFocus:
			{
				input->onRawEventLostFocus();
				break;
			}
			case sf::Event::GainedFocus:
			{
				input->onRawEventGainedFocus();
				break;
			}
			case sf::Event::TextEntered:
			{
				input->onRawEventTextEntered(event.text.unicode);
				break;
			}
			case sf::Event::KeyPressed:
			{
				input->onRawEventKeyPressed(
					kb::sfmlToBlitz(event.key.code), event.key.alt,
						event.key.control, event.key.shift, event.key.system);
				break;
			}
			case sf::Event::KeyReleased:
			{
				input->onRawEventKeyReleased(
					kb::sfmlToBlitz(event.key.code), event.key.alt,
						event.key.control, event.key.shift, event.key.system);
				break;
			}
			case sf::Event::MouseWheelScrolled:
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					input->onRawEventMouseWheelScrolled(
						event.mouseWheelScroll.delta, event.mouseWheelScroll.x,
						event.mouseWheelScroll.y);
				}
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				input->onRawEventMouseButtonPressed(
					mouse::sfmlToBlitz(event.mouseButton.button),
					event.mouseButton.x, event.mouseButton.y);
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				input->onRawEventMouseButtonReleased(
					mouse::sfmlToBlitz(event.mouseButton.button),
					event.mouseButton.x, event.mouseButton.y);
				break;
			}
			case sf::Event::MouseMoved:
			{
				input->onRawEventMouseMoved(event.mouseMove.x,
					event.mouseMove.y);
				break;
			}
			case sf::Event::MouseEntered:
			{
				input->onRawEventMouseEntered();
				break;
			}
			case sf::Event::MouseLeft:
			{
				input->onRawEventMouseLeft();
				break;
			}
			case sf::Event::JoystickButtonPressed:
			case sf::Event::JoystickButtonReleased:
			case sf::Event::JoystickMoved:
			case sf::Event::JoystickConnected:
			case sf::Event::JoystickDisconnected:
			case sf::Event::TouchBegan:
			case sf::Event::TouchMoved:
			case sf::Event::TouchEnded:
			case sf::Event::SensorChanged:
			default: break;
		}
	}
}

void Window::startInWindowedMode(bool value)
{
	shouldStartInWindowedMode = value;
}

void Window::registerInput(Input* input)
{
	assert(this->input == nullptr);
	assert(input != nullptr);
	
	this->input = input;
}
