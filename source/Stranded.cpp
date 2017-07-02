#include "Stranded.h"

#include <iostream>

#include "common/Timer.h"
#include "graphics/Graphics.h"
#include "network/Network.h"
#include "sound/Sound.h"

Stranded::Stranded(std::vector<std::string> const & arguments) :
	cmdLineArgs(arguments),
	modification(cmdLineArgs.modificationName()),
	window(cmdLineArgs.shouldForceWindowedMode(), modification),
	input(window, modification),
	quitEventHandler(new QuitEventHandler(&input, *this)),
	graphics(new gfx::Graphics(input)),
	network(),
	sound(),
	engine(input, *graphics, *network, *sound),
	shouldStop(false)
{
	this->init();

	quitEventHandler->init();
}

bool Stranded::init()
{
	if (!graphics->init(modification))
	{
		return false;
	}

	if (!engine.init(modification))
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

		input.update(deltaTime);

		engine.update(deltaTime);

		graphics->update(deltaTime);

		graphics->drawAll();

		window.display();
	}
}

void Stranded::stop()
{
	shouldStop = true;
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
