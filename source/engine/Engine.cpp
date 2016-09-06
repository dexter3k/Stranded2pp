#include "Engine.h"

#include <cassert>

#include "common/Modification.h"

Engine::Engine(const std::shared_ptr<Input>& input,
		const std::shared_ptr<Graphics>& graphics,
		const std::shared_ptr<Gui>& gui,
		const std::shared_ptr<Network>& network,
		const std::shared_ptr<Sound>& sound) :
	input(input),
	graphics(graphics),
	gui(gui),
	network(network),
	sound(sound),
	gameState(Intro)
{}

Engine::~Engine()
{}

bool Engine::init(const std::shared_ptr<const Modification>& modification)
{
	setGameState(Intro);

	return true;
}

void Engine::update(float deltaTime)
{
	switch (gameState)
	{
		case Intro:
		{
			// Nothing to do
			break;
		}
		case MainMenu:
		case Singleplayer:
		case Multiplayer:
		case Editor:
		{
			break;
		}
		default:
		{
			assert(!"Reached default!");
			break;
		}
	}
}

void Engine::setGameState(GameState newGameState)
{
	// remove old state
	switch (gameState)
	{
		case Intro:
		{
			// Nothing to do
			break;
		}
		case MainMenu:
		{
			break;
		}
		case Singleplayer:
		{
			break;
		}
		case Multiplayer:
		{
			break;
		}
		case Editor:
		{
			break;
		}
		default:
		{
			assert(!"Reached default!");
			break;
		}
	}

	gameState = newGameState;

	switch (gameState)
	{
		case Intro:
		{
			//gui->setScreen(Screen::Intro);

			break;
		}
		case MainMenu:
		{
			break;
		}
		case Singleplayer:
		{
			break;
		}
		case Multiplayer:
		{
			break;
		}
		case Editor:
		{
			break;
		}
		default:
		{
			assert(!"Reached default!");
			break;
		}
	}
}

Engine::GameState Engine::getGameState() const
{
	return gameState;
}
