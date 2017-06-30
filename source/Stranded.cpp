#include "Stranded.h"

#include <iostream>

#include "common/Modification.h"
#include "common/Timer.h"
#include "engine/Engine.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "network/Network.h"
#include "sound/Sound.h"
#include "window/Window.h"

const std::string Stranded::defaultModificationName = "Stranded II";

Stranded::Stranded(std::vector<std::string> const & arguments) :
	modification(new Modification(defaultModificationName)),
	window(new Window()),
	input(new Input(*window)),
	quitEventHandler(new QuitEventHandler(input.get(), *this)),
	graphics(new gfx::Graphics(*input)),
	network(new Network()),
	sound(new Sound()),
	engine(new Engine(*input, *graphics, *network, *sound)),
	shouldStop(false)
{
	this->init(arguments);
}

Stranded::~Stranded()
{}

bool Stranded::init(const std::vector<std::string>& arguments)
{
	if (!parseArguments(arguments))
	{
		return false;
	}

	if (!modification->init())
	{
		return false;
	}

	if (!window->init(*modification))
	{
		return false;
	}

	if (!input->init(*modification))
	{
		return false;
	}

	quitEventHandler->init();

	if (!graphics->init(*modification))
	{
		return false;
	}

	if (!network->init(*modification))
	{
		return false;
	}

	if (!sound->init(*modification))
	{
		return false;
	}

	if (!engine->init(*modification))
	{
		return false;
	}

	return true;
}

void Stranded::run()
{
	printWelcomeMessage();

	float deltaTime = 0.0f;

	Timer deltaTimer;

	while (!shouldStop)
	{
		deltaTime = deltaTimer.restart();

		input->update(deltaTime);

		engine->update(deltaTime);

		graphics->update(deltaTime);

		graphics->drawAll();

		window->display();
	}
}

void Stranded::stop()
{
	shouldStop = true;
}

bool Stranded::parseArguments(const std::vector<std::string>& arguments)
{
	unsigned argumentCount = arguments.size();
	for (unsigned i = 0; i < argumentCount; ++i)
	{
		if (arguments[i] == "-win")
		{
			window->startInWindowedMode(true);
		}
		else if (arguments[i] == "-mod")
		{
			if (++i != argumentCount)
			{
				modification->setName(arguments[i]);
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

void Stranded::printWelcomeMessage()
{
	std::cout << "\n";
	for (unsigned i = 0; i < 80; ++i)
	{
		std::cout << "*";
	}
	std::cout << "\n";
	std::cout << "Welcome to Stranded2++\n";
	std::cout << "Web: www.github.com/SMemsky/Stranded2pp\n";
	std::cout << "Mail: schooldev3000@gmail.com\n";
	std::cout << "Original game: www.stranded.unrealsoftware.de\n";
	for (unsigned i = 0; i < 80; ++i)
	{
		std::cout << "*";
	}
	std::cout << "\n" << std::endl;
}
