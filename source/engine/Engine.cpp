#include "Engine.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include "SaveGameUtils.h"
#include "script/Compiler.h"

#include "common/FileSystem.h"
#include "common/Modification.h"
#include "common/ParseUtils.h"
#include "common/StringUtils.h"
#include "graphics/Graphics.h"
#include "graphics/gui/Gui.h"

const unsigned Engine::gameTimeRatio = 500; // 500ms per game minute

Engine::Engine(Input&, gfx::Graphics& graphics, Network&, Sound&, Modification const & modification) :
	//input(input),
	graphics(graphics),
	//network(network),
	//sound(sound),
	gameState(Intro),
	modBaseDirectory(""),
	scriptContext(),
	gameScriptSource(""),
	mainScript(),
	mapScript(),
	isTimePaused(false),
	timeCounter(0),
	currentDay(0),
	dayTime(0),
	timeChanged(false)
{
	graphics.getGui().connectEngine(this);

	if (!init(modification))
		throw std::runtime_error("Unable to init Engine");
}

bool Engine::init(Modification const & modification)
{
	modBaseDirectory = modification.getPath();

	if (!loadGame())
	{
		return false;
	}

	setGameState(Intro);

	return true;
}

void Engine::update(double deltaTime)
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
				timeCounter += static_cast<long long>(deltaTime * 1000000.0);

				if (timeCounter >= gameTimeRatio * 1000)
				{
					//NOTE: No more than a minute per frame?
					// FPS < 2 will cause problems
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

				// TODO
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
	bool, const std::string& skybox, bool multiplayerMap,
	uint8_t, const std::string&, const std::string&)
{
	if (multiplayerMap)
	{
		std::cout << "Warning: loading multiplayer map in singleplayer" <<
			std::endl;
	}

	currentDay = day;
	dayTime = (hour < 24 ? hour : 0) * 60 + (minute < 60 ? minute : 0);

	graphics.setSkybox(skybox);

	//mapScript.compile(briefScript);
}

void Engine::setupQuickslots(const std::vector<std::string>&)
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

bool Engine::loadGame()
{
	std::vector<std::string> entries;
	fs::scanFolder(modBaseDirectory + "sys/", entries);

	for (auto&& entry : entries)
	{
		if (string::startsWith(entry, "game") &&
			string::endsWith(entry, ".inf"))
		{
			if (!parseGameConfig(std::string("sys/") + entry))
			{
				return false;
			}
		}
	}

	try
	{
		mainScript = script::compile(gameScriptSource);
	}
	catch (std::exception & exception)
	{
		std::cout << exception.what() << std::endl;

		return false;
	}

	return true;
}

bool Engine::parseGameConfig(const std::string& filename)
{
	std::vector<parser::inf::Entry> entries;
	if (!parser::inf::loadAndTokenize(modBaseDirectory + filename, entries))
	{
		return false;
	}

	gameScriptSource.clear();

	for (auto&& entry : entries)
	{
		if (entry.key == "healthsystem")
		{}
		else if (entry.key == "exhaust_move")
		{}
		else if (entry.key == "exhaust_swim")
		{}
		else if (entry.key == "exhaust_jump")
		{}
		else if (entry.key == "exhaust_attack")
		{}
		else if (entry.key == "exhausted_damage")
		{}
		else if (entry.key == "dive_time")
		{}
		else if (entry.key == "dive_damage")
		{}
		else if (entry.key == "default_itemmodel")
		{}
		else if (entry.key == "projectile_lifetime")
		{}
		else if (entry.key == "firerange")
		{}
		else if (entry.key == "dig_time")
		{}
		else if (entry.key == "fish_time")
		{}
		else if (entry.key == "jumptime")
		{}
		else if (entry.key == "jumpfactor")
		{}
		else if (entry.key == "rainratio")
		{}
		else if (entry.key == "snowratio")
		{}
		else if (entry.key == "gore")
		{}
		else if (entry.key == "waverate")
		{}
		else if (entry.key == "minwavespace")
		{}
		else if (entry.key == "combiscreen")
		{}
		else if (entry.key == "scriptlooptimeout")
		{}
		else if (entry.key == "script")
		{
			gameScriptSource += entry.value;
		}
		else if (entry.key == "scriptkey")
		{}
		else if (entry.key == "limit_objects")
		{}
		else if (entry.key == "limit_units")
		{}
		else if (entry.key == "limit_items")
		{}
		else if (entry.key == "menu_adventure")
		{}
		else if (entry.key == "menu_random")
		{}
		else if (entry.key == "menu_loadsave")
		{}
		else if (entry.key == "menu_singleplayer")
		{}
		else if (entry.key == "menu_multiplayer")
		{}
		else if (entry.key == "menu_editor")
		{}
		else if (entry.key == "menu_credits")
		{}
		else if (entry.key == "firelightsize")
		{}
		else if (entry.key == "firelightbrightness")
		{}
		else if (entry.key == "terrain_color_normal")
		{}
		else if (entry.key == "terrain_color_desert")
		{}
		else if (entry.key == "terrain_color_snow")
		{}
		else if (entry.key == "terrain_color_swamp")
		{}
		else if (entry.key == "showemptybuildinggroups")
		{}
		else if (entry.key == "falltime")
		{}
		else if (entry.key == "falldamage")
		{}
		else if (entry.key == "falldamageminy")
		{}
		else if (entry.key == "falldamagemaxy")
		{}
		else
		{
			std::cout << filename << ":" << entry.key << ": " << "Unknown key"
				<< std::endl;

			return false;
		}
	}

	std::cout << "'" << filename << "' is loaded successfully" << std::endl;

	return true;
}
