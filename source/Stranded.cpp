#include "Stranded.h"

#include <iostream>

#include "common/Timer.h"

std::string const Stranded::versionString = "Stranded2++ engine by Dexter3000. Version 0.0 (indev)";

Stranded::Stranded(std::vector<std::string> const & arguments) :
	cmdLineArgs(arguments),
	modification(cmdLineArgs.modificationName()),
	resources(cmdLineArgs.modificationName()),
	strings(modification.getPath()),
	window(cmdLineArgs.shouldForceWindowedMode(), modification),
	input(window, modification),
	graphics(modification),
	engine(*this, graphics, network, sound, modification),
	editor(*this),
	intro(*this),
	mainMenu(*this),
	stateMapping({
		{state::EditorState, &editor},
		{state::IntroState, &intro},
		{state::MainMenuState, &mainMenu}}),
	currentStates(),
	shouldStop(false)
{}

void Stranded::run()
{
	shouldStop = false;

	printWelcomeMessage();
	setState(state::IntroState);

	Timer deltaTimer;
	double deltaTime = 0.0;

	while (!shouldStop) {
		// Process all OS events
		input.processInput(deltaTime);

		// Pass events to graphics layer and then game engine
		Event event;
		while (input.getEvent(event)) {
			if (currentStates.empty() || !(currentStates.top()->processEvent(event))) {
				if (!graphics.processEvent(event)) {
					if (!engine.processEvent(event)
						&& event.type == Event::Closed)
					{
						stopLoop();
					}
				}
			}
		}

		// Manage state logic
		if (!currentStates.empty())
			currentStates.top()->update(deltaTime);

		// Update current engine stage's logic
		engine.update(deltaTime);

		// Graphics module pre-render update
		graphics.update(deltaTime);

		// Render the scene
		graphics.drawAll();

		// Swap buffers
		window.display();

		// Calculate time for the next frame.
		// This is just to make the first delta be exactly zero seconds long
		deltaTime = deltaTimer.restart();
	}

	while (!currentStates.empty())
		popState();
}

void Stranded::stopLoop()
{
	shouldStop = true;
}

void Stranded::pushState(state::Type state)
{
	std::cout << "Pushing state " << state << std::endl;

	if (!currentStates.empty())
		currentStates.top()->hide();

	try {
		currentStates.push(stateMapping.at(state));
	} catch (std::out_of_range &) {
		assert(false);
	}

	currentStates.top()->show();
}

void Stranded::popState()
{
	std::cout << "Popping state" << std::endl;

	assert(!currentStates.empty());

	currentStates.top()->hide();
	currentStates.pop();

	if (!currentStates.empty())
		currentStates.top()->show();
}

void Stranded::setState(state::Type state)
{
	while (!currentStates.empty())
		popState();

	pushState(state);
}

void Stranded::printWelcomeMessage()
{
	std::cout << "\n";
	std::cout << std::string(80, '*');
	std::cout << "\n";
	std::cout << "Welcome to Stranded2++\n";
	std::cout << "Web: www.github.com/SMemsky/Stranded2pp\n";
	std::cout << "Mail: schooldev3000@gmail.com\n";
	std::cout << "Original game: www.stranded.unrealsoftware.de\n";
	std::cout << std::string(80, '*');
	std::cout << "\n" << std::endl;
}
