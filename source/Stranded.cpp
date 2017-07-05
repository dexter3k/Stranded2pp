#include "Stranded.h"

#include <iostream>

#include "common/Timer.h"

Stranded::Stranded(std::vector<std::string> const & arguments) :
	cmdLineArgs(arguments),
	modification(cmdLineArgs.modificationName()),
	window(cmdLineArgs.shouldForceWindowedMode(), modification),
	input(window, modification),
	graphics(input, modification),
	network(),
	sound(),
	engine(input, graphics, network, sound, modification),
	shouldStop(false)
{}

void Stranded::run()
{
	printWelcomeMessage();

	Timer deltaTimer;
	double deltaTime = 0.0;

	while (!shouldStop)
	{
		input.processInput(deltaTime);

		engine.update(deltaTime);

		graphics.update(deltaTime);

		graphics.drawAll();

		window.display();

		// Calculate time for the next frame.
		// This is just to make the first delta be exactly zero seconds long
		deltaTime = deltaTimer.restart();
	}
}

void Stranded::stopLoop()
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
