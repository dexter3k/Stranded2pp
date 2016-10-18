#include "Engine.h"

#include <cassert>
#include <iostream>

#include "SaveGameUtils.h"

#include "common/Modification.h"
#include "graphics/gui/Gui.h"
#include "graphics/Graphics.h"

Engine::Engine(Input& input, gfx::Graphics& graphics, Network& network,
		Sound& sound) :
	input(input),
	graphics(graphics),
	network(network),
	sound(sound),
	gameState(Intro),
	modBaseDirectory("")
{
	graphics.getGui().connectEngine(this);
}

Engine::~Engine()
{}

bool Engine::init(const Modification& modification)
{
	modBaseDirectory = modification.getPath();

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
	std::cout << "Setting game state" << std::endl;
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
			graphics.getGui().setScreen(gfx::gui::Screen::Intro);

			break;
		}
		case MainMenu:
		{
			if (!save::loadFromFile(
				modBaseDirectory + "maps/menu/menu.s2", *this))
			{
				std::cout << "Error occured while loading menu map!" <<
					std::endl;

				//input.raiseEvent(closed) ?

				break;
			}

			graphics.getGui().setScreen(gfx::gui::Screen::MainMenu);

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

void Engine::skipIntro()
{
	if (gameState == Intro)
	{
		setGameState(MainMenu);
	}
}
