#include "Engine.h"

#include <cassert>
#include <cmath>
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

void Engine::resetGame()
{
	
}

void Engine::setupGame(uint32_t day, uint8_t hour, uint8_t minute,
	bool timeIsFreezed, const std::string& skybox, bool multiplayerMap,
	uint8_t climate, const std::string& music, const std::string& briefScript)
{
	graphics.setSkybox(skybox);
}

void Engine::setupQuickslots(const std::vector<std::string>& quickslots)
{
	// Setup those quickslots
}

void Engine::setupTerrain(unsigned terrainSize,
	const std::vector<float>& heightMap, unsigned colorMapSize,
	const std::vector<gfx::Color>& colorMap,
	const std::vector<uint8_t>& grassMap)
{
	if (terrainSize < 16 ||
		!math::isPowerOfTwo(terrainSize))
	{
		std::cout << "Invalid terrain size: " << terrainSize << std::endl;

		// TODO
		return;
	}

	// Stranded uses left-handed coordinate system, so we must flip heightmap
	// on z-axis
	unsigned heightMapSize = terrainSize + 1;
	std::vector<float> flippedHeightMap(heightMap.size());
	for (unsigned x = 0; x < heightMapSize; ++x)
	{
		for (unsigned z = 0; z < heightMapSize; ++z)
		{
			flippedHeightMap[x + (heightMapSize - z - 1) * (heightMapSize)] =
				heightMap[x + z * (heightMapSize)];
		}
	}

	graphics.setTerrain(terrainSize, flippedHeightMap, colorMapSize, colorMap,
		grassMap);
	graphics.setWaterLevel(1.0f / 64.0f);
}
