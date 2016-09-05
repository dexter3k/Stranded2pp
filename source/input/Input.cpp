#include "Input.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include "common/Modification.h"
#include "window/Window.h"

#include "Stranded.h"

const std::string Input::keyNameInfoPath = "sys/keys.inf";
const std::string Input::defaultName = "null";

Input::Input(const std::shared_ptr<Window>& window) :
	window(window),
	mouseButtonNames(6, defaultName),
	mouseWheelUpName(defaultName),
	mouseWheelDownName(defaultName),
	keyNames(256, defaultName)
{}

Input::~Input()
{}

bool Input::init(const std::shared_ptr<const Modification>& modification)
{
	if (!loadKeyNames(modification->getPath()))
	{
		return false;
	}

	return true;
}

void Input::update(float deltaTime)
{
	window->pollEvents();
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
	//std::cout << "Raw closed" << std::endl;
	//Stranded::debug_stop();
}

void Input::onRawEventResized(unsigned newWidth, unsigned newHeight)
{

}

void Input::onRawEventLostFocus()
{

}

void Input::onRawEventGainedFocus()
{

}

void Input::onRawEventTextEntered(uint32_t symbol)
{

}

void Input::onRawEventKeyPressed(uint8_t key, bool alt, bool control,
	bool shift, bool super)
{
	std::cout << "Raw key press: " << getKeyName(key) << std::endl;
}

void Input::onRawEventKeyReleased(uint8_t key, bool alt, bool control,
	bool shift, bool super)
{

}

void Input::onRawEventMouseWheelScrolled(float delta, int x, int y)
{

}

void Input::onRawEventMouseButtonPressed(uint8_t button, int x, int y)
{

}

void Input::onRawEventMouseButtonReleased(uint8_t button, int x, int y)
{

}

void Input::onRawEventMouseMoved(int x, int y)
{

}

void Input::onRawEventMouseEntered()
{

}

void Input::onRawEventMouseLeft()
{

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
					std::cout << keyNameInfoPath << ":" << lineCounter << ": " <<
						"Unknown key" << std::endl;

					return false;
				}

				if (key >= 6)
				{
					std::cout << keyNameInfoPath << ":" << lineCounter << ": " <<
						"Key is out of bounds" << std::endl;

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
					std::cout << keyNameInfoPath << ":" << lineCounter << ": " <<
						"Unknown key" << std::endl;

					return false;
				}

				if (key >= 256)
				{
					std::cout << keyNameInfoPath << ":" << lineCounter << ": " <<
						"Key is out of bounds" << std::endl;

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
