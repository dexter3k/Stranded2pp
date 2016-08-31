#include "Stranded.h"

#include <iostream>

#include "common/FileSystem.h"
#include "engine/Engine.h"
#include "graphics/Graphics.h"
#include "gui/Gui.h"
#include "input/Input.h"
#include "network/Network.h"
#include "sound/Sound.h"
#include "window/Window.h"

Stranded::Stranded() :
	modification("Stranded II"),
	isFullscreen(false),
	window(new Window()),
	input(new Input(window)),
	graphics(new Graphics(input)),
	gui(new Gui(input)),
	network(new Network()),
	sound(new Sound()),
	engine(new Engine(input, graphics, gui, network, sound))
{}

Stranded::~Stranded()
{}

bool Stranded::init(const std::vector<std::string>& arguments)
{
	if (!parseArguments(arguments))
	{
		return false;
	}

	// Check mod path
	if (!fs::checkFolderExists(std::string("mods/") + modification))
	{
		std::cout << "Error: mod '" << modification <<
			"' is missing from 'mods' folder!" << std::endl;
		return false;
	}

	

	return true;
}

void Stranded::run()
{}

bool Stranded::parseArguments(const std::vector<std::string>& arguments)
{
	unsigned argumentCount = arguments.size();
	for (unsigned i = 0; i < argumentCount; ++i)
	{
		if (arguments[i] == "-win")
		{
			isFullscreen = false;
		}
		else if (arguments[i] == "-mod")
		{
			if (++i != argumentCount)
			{
				modification = arguments[i];
			}
			else
			{
				std::cout << "Error: argument for '" << arguments[i-1] <<
					"' is missing!" << std::endl;

				return false;
			}
		}
		else
		{
			std::cout << "Error: argument '" << arguments[i] << "' is invalid!"
				<< std::endl;

			return false;
		}
	}

	return true;
}
