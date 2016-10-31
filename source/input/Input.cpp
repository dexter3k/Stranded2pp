#include "Input.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "RawInputHandler.h"

#include "common/Modification.h"
#include "window/Window.h"

#include "Stranded.h"

#include "common/ParseUtils.h"
#include "common/StringUtils.h"

const std::string Input::keyNameInfoPath = "sys/keys.inf";
const std::string Input::defaultName = "null";

Input::Input(Window& window) :
	window(window),
	mouseButtonNames(6, defaultName),
	mouseWheelUpName(defaultName),
	mouseWheelDownName(defaultName),
	keyNames(256, defaultName),
	rawInputHandlers()
{}

Input::~Input()
{}

bool Input::init(const Modification& modification)
{
	if (!loadKeyNames(modification.getPath()))
	{
		return false;
	}

	window.registerInput(this);

	return true;
}

void Input::update(float deltaTime)
{
	window.pollEvents();
}

std::string Input::getMouseButtonName(uint8_t button) const
{
	if (button >= mouseButtonNames.size())
	{
		return defaultName;
	}

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
	for (auto& handler : rawInputHandlers)
	{
		handler->onClosed();
	}
}

void Input::onRawEventResized(unsigned newWidth, unsigned newHeight)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onResized(newWidth, newHeight);
	}
}

void Input::onRawEventLostFocus()
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onLostFocus();
	}
}

void Input::onRawEventGainedFocus()
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onGainedFocus();
	}
}

void Input::onRawEventTextEntered(uint32_t symbol)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onTextEntered(symbol);
	}
}

void Input::onRawEventKeyPressed(uint8_t key, bool alt, bool control,
	bool shift, bool super)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onKeyPressed(key, alt, control, shift, super);
	}
}

void Input::onRawEventKeyReleased(uint8_t key, bool alt, bool control,
	bool shift, bool super)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onKeyReleased(key, alt, control, shift, super);
	}
}

void Input::onRawEventMouseWheelScrolled(float delta, int x, int y)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onMouseWheelScrolled(delta, x, y);
	}
}

void Input::onRawEventMouseButtonPressed(uint8_t button, int x, int y)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onMouseButtonPressed(button, x, y);
	}
}

void Input::onRawEventMouseButtonReleased(uint8_t button, int x, int y)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onMouseButtonReleased(button, x, y);
	}
}

void Input::onRawEventMouseMoved(int x, int y)
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onMouseMoved(x, y);
	}
}

void Input::onRawEventMouseEntered()
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onMouseEntered();
	}
}

void Input::onRawEventMouseLeft()
{
	for (auto& handler : rawInputHandlers)
	{
		handler->onMouseLeft();
	}
}

void Input::addRawInputHandler(RawInputHandler* rawInputHandler)
{
	assert(rawInputHandler != nullptr);

	std::cout << "Adding handler: " << rawInputHandler << std::endl;

	unsigned size = rawInputHandlers.size();
	for (unsigned i = 0; i < size; ++i)
	{
		assert(rawInputHandlers[i] != rawInputHandler);
	}

	rawInputHandlers.push_back(rawInputHandler);
}

void Input::removeRawInputHandler(RawInputHandler* rawInputHandler)
{
	assert(rawInputHandler != nullptr);

	std::cout << "Removing handler: " << rawInputHandler << std::endl;

	unsigned size = rawInputHandlers.size();
	for (unsigned i = 0; i < size; ++i)
	{
		if (rawInputHandlers[i] == rawInputHandler)
		{
			rawInputHandlers.erase(rawInputHandlers.begin() + i);
			return;
		}
	}

	assert(false);
}

bool Input::loadKeyNames(const std::string& modificationPath)
{
	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(modificationPath + keyNameInfoPath,
		entries))
	{
		return false;
	}

	for (auto&& entry : entries)
	{
		if (entry.type != parser::inf::Entry::Value)
		{
			std::cout << keyNameInfoPath << ":" << entry.key << ": " <<
				"Value expected" << std::endl;

			return false;
		}

		try
		{
			if (string::startsWith(entry.key, "mouse"))
			{
				unsigned key = std::stoul(
					entry.key.substr(std::string("mouse").size()));

				if (key > 5)
				{
					std::cout << keyNameInfoPath << ":" << entry.key << ": "
						<< "Key is out of bounds" << std::endl;

					return false;
				}

				mouseButtonNames[key] = entry.value;
			}
			else if (string::startsWith(entry.key, "mwheelup"))
			{
				mouseWheelUpName = entry.value;
			}
			else if (string::startsWith(entry.key, "mwheeldown"))
			{
				mouseWheelDownName = entry.value;
			}
			else
			{
				unsigned key = std::stoul(entry.key);

				if (key > 255)
				{
					std::cout << keyNameInfoPath << ":" << entry.key << ": "
						<< "Key is out of bounds" << std::endl;

					return false;
				}

				keyNames[key] = entry.value;
			}
		}
		catch (std::invalid_argument& exception)
		{
			std::cout << keyNameInfoPath << ":" << entry.key << ": "
				<< "Unknown key" << std::endl;

			return false;
		}
	}

	std::cout << "'" << keyNameInfoPath << "' is loaded successfully" <<
		std::endl;

	return true;
}
