#include "Input.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "RawInputHandler.h"

#include "common/Modification.h"
#include "window/Window.h"

#include "Stranded.h"

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
	std::ifstream keysInfo(modificationPath + keyNameInfoPath);
	if (keysInfo)
	{
		std::string line;
		unsigned lineCounter = 0;
		while (std::getline(keysInfo, line))
		{
			++lineCounter;

			line = line.substr(line.find_first_not_of(" \t"));

			if (line.empty() ||
				line[0] == '#' ||
				line[0] == '\r' ||
				line[0] == '\n')
			{
				continue;
			}

			std::string keyString = line.substr(0, line.find('='));

			if (keyString.find("mouse") == 0)
			{
				keyString = keyString.substr(std::string("mouse").size());

				unsigned key = 0;
				try
				{
					key = std::stoul(keyString);
				}
				catch (std::exception& exception)
				{
					std::cout << keyNameInfoPath << ":" << lineCounter << ": "
						<< "Unknown key" << std::endl;

					return false;
				}

				if (key >= 6)
				{
					std::cout << keyNameInfoPath << ":" << lineCounter << ": "
						<< "Key is out of bounds" << std::endl;

					return false;
				}

				std::string value = line.substr(line.find('=') + 1);
				value = value.substr(0, value.find_last_not_of(" \t\r\n") + 1);

				mouseButtonNames[key] = value;
			}
			else if (keyString.find("mwheelup") == 0)
			{
				std::string value = line.substr(line.find('=') + 1);
				value = value.substr(0, value.find_last_not_of(" \t\r\n") + 1);

				mouseWheelUpName = value;
			}
			else if (keyString.find("mwheeldown") == 0)
			{
				std::string value = line.substr(line.find('=') + 1);
				value = value.substr(0, value.find_last_not_of(" \t\r\n") + 1);

				mouseWheelDownName = value;
			}
			else
			{
				unsigned key = 0;
				try
				{
					key = std::stoul(keyString);
				}
				catch (std::exception& exception)
				{
					std::cout << keyNameInfoPath << ":" << lineCounter << ": "
						<< "Unknown key" << std::endl;

					return false;
				}

				if (key >= 256)
				{
					std::cout << keyNameInfoPath << ":" << lineCounter << ": "
						<< "Key is out of bounds" << std::endl;

					return false;
				}

				std::string value = line.substr(line.find('=') + 1);
				value = value.substr(0, value.find_last_not_of(" \t\r\n") + 1);

				keyNames[key] = value;
			}
		}

		keysInfo.close();
	}
	else
	{
		std::cout << "Unable to open file '" << modificationPath +
			keyNameInfoPath << "'" << std::endl;
		return false;
	}

	std::cout << "'" << keyNameInfoPath << "' is loaded successfully" <<
		std::endl;

	return true;
}
