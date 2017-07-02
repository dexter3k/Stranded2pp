#include "Stranded.h"

#include <iostream>

#include "common/Timer.h"

Stranded::Stranded(std::vector<std::string> const & arguments) :
	cmdLineArgs(arguments),
	modification(cmdLineArgs.modificationName()),
	window(cmdLineArgs.shouldForceWindowedMode(), modification),
	input(window, modification),
	quitEventHandler(&input, *this),
	graphics(input, modification),
	network(),
	sound(),
	engine(input, graphics, network, sound, modification),
	shouldStop(false)
{
	quitEventHandler.attach();
}

void Stranded::run()
{
	printWelcomeMessage();

	double deltaTime = 0.0f;

	Timer deltaTimer;

	while (!shouldStop)
	{
		deltaTime = deltaTimer.restart();

		input.update(deltaTime);

		engine.update(deltaTime);

		graphics.update(deltaTime);

		graphics.drawAll();

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
		std::cout << "*";
	std::cout << "\n";
	std::cout << "Welcome to Stranded2++\n";
	std::cout << "Web: www.github.com/SMemsky/Stranded2pp\n";
	std::cout << "Mail: schooldev3000@gmail.com\n";
	std::cout << "Original game: www.stranded.unrealsoftware.de\n";
	for (unsigned i = 0; i < 80; ++i)
		std::cout << "*";
	std::cout << "\n" << std::endl;
}
