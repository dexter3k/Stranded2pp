#include "Engine.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include "SaveGameUtils.h"

#include "common/Modification.h"
#include "graphics/gui/Gui.h"
#include "graphics/Graphics.h"

const unsigned Engine::gameTimeRatio = 500; // 500ms per game minute

Engine::Engine(Input& input, gfx::Graphics& graphics, Network& network,
		Sound& sound) :
	input(input),
	graphics(graphics),
	network(network),
	sound(sound),
	gameState(Intro),
	modBaseDirectory(""),
	isTimePaused(false),
	timeCounter(0),
	currentDay(0),
	dayTime(0),
	timeChanged(false)
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
		{
			if (!isTimePaused)
			{
				timeCounter += static_cast<long long>(deltaTime * 1000000.0f);

				if (timeCounter >= gameTimeRatio * 1000)
				{
					// No more than a minute per frame?
					timeCounter -= gameTimeRatio * 1000;

					++dayTime;

					if (dayTime == 24 * 60)
					{
						dayTime = 0;

						++currentDay;
					}

					timeChanged = true;
				}
				else
				{
					timeChanged = false;
				}
			}
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
	isTimePaused = false;
	timeCounter = 0;
	currentDay = 0;
	dayTime = 0;
}

void Engine::setupGame(uint32_t day, uint8_t hour, uint8_t minute,
	bool timeIsFreezed, const std::string& skybox, bool multiplayerMap,
	uint8_t climate, const std::string& music, const std::string& briefScript)
{
	if (multiplayerMap)
	{
		std::cout << "Warning: loading multiplayer map in singleplayer" <<
			std::endl;
	}

	currentDay = day;
	dayTime = (hour < 24 ? hour : 0) * 60 + (minute < 60 ? minute : 0);

	graphics.setSkybox(skybox);
}

void Engine::setupQuickslots(const std::vector<std::string>& quickslots)
{
	// Setup those quickslots
}

bool Engine::setupTerrain(unsigned terrainSize,
	const std::vector<float>& heightMap, unsigned colorMapSize,
	const std::vector<gfx::Color>& colorMap,
	const std::vector<uint8_t>& grassMap)
{
	if (terrainSize < 16 ||
		!math::isPowerOfTwo(terrainSize))
	{
		std::cout << "Invalid terrain size: " << terrainSize << std::endl;

		return false;
	}

	// Stranded uses left-handed coordinate system, so we must flip heightmap
	// on z-axis
	unsigned heightMapSize = terrainSize + 1;
	std::vector<float> flippedHeightMap(heightMap.size());
	for (unsigned x = 0; x < heightMapSize; ++x)
	{
		for (unsigned z = 0; z < heightMapSize; ++z)
		{
			flippedHeightMap[x + (heightMapSize - z - 1) * heightMapSize] =
				heightMap[x + z * heightMapSize];
		}
	}

	graphics.setTerrain(terrainSize, flippedHeightMap, colorMapSize, colorMap,
		grassMap);

	return true;
}
