#include "Input.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Stranded.h"
#include "common/Modification.h"
#include "utils/ParseUtils.h"
#include "utils/StringUtils.h"
#include "window/Window.h"

const std::string Input::keyNameInfoPath = "sys/keys.inf";
const std::string Input::defaultName = "null";

Input::Input(Window & window, Modification const & modification) :
	window(window),
	events(),
	mouseButtonNames(6, defaultName),
	mouseWheelUpName(defaultName),
	mouseWheelDownName(defaultName),
	keyNames(256, defaultName)
{
	// TODO
	if (!loadKeyNames(modification.getPath()))
		throw std::runtime_error("Unable to init Input");

	window.registerInput(this);
}

void Input::processInput(double /* deltaTime */)
{
	while (!events.empty())
		events.pop();

	// This will trigger Input::onRawEvent* callbacks
	window.pollEvents();
}

bool Input::getEvent(Event & event)
{
	if (events.empty())
		return false;

	event = events.front();
	events.pop();

	return true;
}

// Does this really belong to Input? Hmmm :thinking:
std::string Input::getMouseButtonName(uint8_t button) const
{
	if (button >= mouseButtonNames.size())
		return defaultName;

	return mouseButtonNames[button];
}

std::string Input::getMouseWheelUpName() const
{
	return mouseWheelUpName;
}

std::string Input::getMouseWheelDownName() const
{
	return mouseWheelDownName;
}

std::string Input::getKeyName(uint8_t key) const
{
	return keyNames[key];
}

void Input::onRawEventClosed()
{
	Event event;
	event.type = Event::Closed;

	events.push(event);
}

void Input::onRawEventResized(unsigned newWidth, unsigned newHeight)
{
	Event event;
	event.type = Event::Resized;
	event.resized.newWidth = newWidth;
	event.resized.newHeight = newHeight;

	events.push(event);
}

void Input::onRawEventLostFocus()
{
	Event event;
	event.type = Event::FocusLost;

	events.push(event);
}

void Input::onRawEventGainedFocus()
{
	Event event;
	event.type = Event::FocusGained;

	events.push(event);
}

void Input::onRawEventTextEntered(uint32_t symbol)
{
	Event event;
	event.type = Event::TextEntered;
	event.textEntered.symbol = symbol;

	events.push(event);
}

void Input::onRawEventKeyPressed(uint8_t key, bool alt, bool control, bool shift, bool super)
{
	Event event;
	event.type = Event::KeyPressed;
	event.keyPressed.key = key;
	event.keyPressed.alt = alt;
	event.keyPressed.control = control;
	event.keyPressed.shift = shift;
	event.keyPressed.super = super;

	events.push(event);
}

void Input::onRawEventKeyReleased(uint8_t key, bool alt, bool control, bool shift, bool super)
{
	Event event;
	event.type = Event::KeyReleased;
	event.keyPressed.key = key;
	event.keyPressed.alt = alt;
	event.keyPressed.control = control;
	event.keyPressed.shift = shift;
	event.keyPressed.super = super;

	events.push(event);
}

void Input::onRawEventMouseWheelScrolled(double delta, int x, int y)
{
	Event event;
	event.type = Event::MouseWheelScrolled;
	event.mouseWheelScrolled.delta = delta;
	event.mouseWheelScrolled.x = x;
	event.mouseWheelScrolled.y = y;

	events.push(event);
}

void Input::onRawEventMouseButtonPressed(uint8_t button, int x, int y)
{
	Event event;
	event.type = Event::MouseButtonPressed;
	event.mouseButtonPressed.button = button;
	event.mouseButtonPressed.x = x;
	event.mouseButtonPressed.y = y;

	events.push(event);
}

void Input::onRawEventMouseButtonReleased(uint8_t button, int x, int y)
{
	Event event;
	event.type = Event::MouseButtonReleased;
	event.mouseButtonReleased.button = button;
	event.mouseButtonReleased.x = x;
	event.mouseButtonReleased.y = y;

	events.push(event);
}

void Input::onRawEventMouseMoved(int x, int y)
{
	Event event;
	event.type = Event::MouseMoved;
	event.mouseMoved.x = x;
	event.mouseMoved.y = y;

	events.push(event);
}

bool Input::loadKeyNames(std::string const & modificationPath)
{
	// TODO: look at this function

	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(modificationPath + keyNameInfoPath, entries))
		return false;

	for (auto&& entry : entries) {
		if (entry.type != parser::inf::Entry::Value) {
			std::cout << keyNameInfoPath << ":" << entry.key << ": " <<
				"Value expected" << std::endl;

			return false;
		}

		try {
			if (string::startsWith(entry.key, "mouse")) {
				unsigned key = std::stoul(entry.key.substr(std::string("mouse").size()));

				if (key > 5) {
					std::cout << keyNameInfoPath << ":" << entry.key << ": "
						<< "Key is out of bounds" << std::endl;

					return false;
				}

				mouseButtonNames[key] = entry.value;
			} else if (string::startsWith(entry.key, "mwheelup")) {
				mouseWheelUpName = entry.value;
			} else if (string::startsWith(entry.key, "mwheeldown")) {
				mouseWheelDownName = entry.value;
			} else {
				unsigned key = std::stoul(entry.key);

				if (key > 255) {
					std::cout << keyNameInfoPath << ":" << entry.key << ": "
						<< "Key is out of bounds" << std::endl;

					return false;
				}

				keyNames[key] = entry.value;
			}
		} catch (std::invalid_argument & exception) {
			std::cout << keyNameInfoPath << ":" << entry.key << ": " << "Unknown key" << std::endl;

			return false;
		}
	}

	std::cout << "'" << keyNameInfoPath << "' is loaded successfully" << std::endl;

	return true;
}
