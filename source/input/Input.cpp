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
	window.pollEvents();
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
{}

void Input::onRawEventResized(unsigned /* newWidth */, unsigned /* newHeight */)
{}

void Input::onRawEventLostFocus()
{}

void Input::onRawEventGainedFocus()
{}

void Input::onRawEventTextEntered(uint32_t /* symbol */)
{}

void Input::onRawEventKeyPressed(uint8_t, bool, bool, bool, bool)
{}

void Input::onRawEventKeyReleased(uint8_t, bool, bool, bool, bool)
{}

void Input::onRawEventMouseWheelScrolled(float, int, int)
{}

void Input::onRawEventMouseButtonPressed(uint8_t, int, int)
{}

void Input::onRawEventMouseButtonReleased(uint8_t, int, int)
{}

void Input::onRawEventMouseMoved(int, int)
{}

bool Input::loadKeyNames(std::string const & modificationPath)
{
	// TODO: look at this function

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
