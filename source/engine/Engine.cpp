#include "Engine.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include "SaveGameUtils.h"
#include "controller/MainMenuController.h"
#include "script/Compiler.h"

#include "Stranded.h"
#include "common/FileSystem.h"
#include "common/Modification.h"
#include "graphics/Graphics.h"
#include "graphics/gui/Gui.h"
#include "utils/ParseUtils.h"
#include "utils/StringUtils.h"

unsigned const Engine::msPerGameMinute = 500;

Engine::Engine(Stranded &, gfx::Graphics & graphics, Network &, Sound &, Modification const & modification) :
	//game(game),
	graphics(graphics),
	//network(network),
	//sound(sound),
	modBaseDirectory(modification.getPath()),
	mainScript(),
	mapScript(),
	// extensionScripts(),
	scheduledTasks(),
	currentController(nullptr),
	gameConfig(mod::loadGameConfig(modBaseDirectory)),
	gameStates(mod::loadStates(modBaseDirectory)),
	gameObjects(mod::loadObjects(modBaseDirectory)),
	objects(),
	isTimePaused(false),
	timeCounter(0),
	currentDay(0),
	dayTime(0),
	timeChanged(false)
{
	try {
		mainScript = script::compile(gameConfig.script);
	} catch (std::exception & exception) {
		std::cout << exception.what() << std::endl;

		throw std::runtime_error("Unable to init Engine");
	}
}

bool Engine::processEvent(Event event)
{
	if (currentController != nullptr
		&& currentController->processEvent(event))
	{
		return true;
	}

	switch (event.type) {
	default:
		return false;
	}
}

void Engine::update(double deltaTime)
{
	timeChanged = updateTime(deltaTime);
}

void Engine::resetGame()
{
	isTimePaused = false;
	timeCounter = 0;
	currentDay = 0;
	dayTime = 0;
}

void Engine::setupGame(uint32_t day, uint8_t hour, uint8_t minute,
	bool, std::string const & skybox, bool multiplayerMap,
	uint8_t, std::string const &, std::string const & briefScript)
{
	if (multiplayerMap) {
		std::cout << "Warning: loading multiplayer map in singleplayer" << std::endl;
	}

	currentDay = day;
	dayTime = (hour < 24 ? hour : 0) * 60 + (minute < 60 ? minute : 0);

	graphics.setSkybox(skybox);

	std::cout << "Brief script: " << briefScript << std::endl;

	mapScript = script::compile(briefScript);
}

void Engine::setupQuickslots(std::vector<std::string> const &)
{}

bool Engine::setupTerrain(unsigned terrainSize,
	std::vector<float> const & heightMap, unsigned colorMapSize,
	std::vector<gfx::Color> const & colorMap,
	std::vector<uint8_t> const & grassMap)
{
	if (terrainSize < 16
		|| !math::isPowerOfTwo(terrainSize))
	{
		std::cout << "Invalid terrain size: " << terrainSize << std::endl;

		return false;
	}

	// TODO
	// Stranded uses left-handed coordinate system, so we must flip heightmap
	// on z-axis
	unsigned heightMapSize = terrainSize + 1;
	std::vector<float> flippedHeightMap(heightMap.size());
	for (unsigned x = 0; x < heightMapSize; ++x) {
		for (unsigned z = 0; z < heightMapSize; ++z) {
			flippedHeightMap[x + (heightMapSize - z - 1) * heightMapSize] = heightMap[x + z * heightMapSize];
		}
	}

	graphics.setTerrain(terrainSize, flippedHeightMap, colorMapSize, colorMap, grassMap);

	return true;
}

void Engine::onPreload()
{
	scheduleEvent("preload");
	handleScheduledEvent("preload");
}

void Engine::loadGame(std::string const & filename, controller::Type controller)
{
	resetGame();
	save::loadFromFile(modBaseDirectory + filename, *this);
	switchController(controller);
}

void Engine::placeObject(unsigned, unsigned objectType, float x, float z,
	float, float, float, unsigned)
{
	auto & go = gameObjects[objectType];
	if (go.id != objectType + 1) {
		std::cout << "Unknown object id: " << objectType << std::endl;
		return ;
	}
	std::cout << gameObjects[objectType].modelName << std::endl;

	auto obj = std::make_unique<Object>(go);

	auto entity = graphics.loadObjectModelAndAddToScene(obj.get());
	entity->setPosition(math::Vector3f(x, 100.0, z));

	objects.push_back(std::move(obj));

	std::cout << objects.size() << std::endl;
}

void Engine::placeUnit(unsigned, unsigned, float, float, float, float,
	float, float, float, float, float, float, float)
{}

void Engine::placeItem(unsigned, unsigned, float, float, float, float,
	float, unsigned, unsigned, unsigned, unsigned)
{}

void Engine::placeInfo(unsigned, unsigned, float, float, float, float, float,
	std::string const &)
{}

void Engine::placeState(unsigned, unsigned, unsigned,
	float, float, float, float, float, float,
	unsigned, float, std::string const &)
{}

void Engine::addExtension(unsigned, unsigned, unsigned, unsigned,
	std::string const &, std::string const &, std::string const &)
{}

void Engine::setCameraRotation(float, float)
{}

bool Engine::updateTime(double deltaTime)
{
	// Note: in-game time will only be udated once per frame
	// This will not cause problems in normal circustanses

	if (!isTimePaused)
	{
		// Is this precision really needed?
		timeCounter += static_cast<long long>(deltaTime * 1000000.0);

		if (timeCounter >= msPerGameMinute * 1000)
		{
			timeCounter -= msPerGameMinute * 1000;

			++dayTime;

			currentDay += dayTime / (24 * 60);
			dayTime %= (24 * 60);

			//std::cout << dayTime / 60 << ":" << dayTime % 60 << ", Day " << currentDay << std::endl;

			return true;
		}
	}

	return false;
}

void Engine::switchController(controller::Type controller)
{
	switch (controller) {
	case controller::MainMenu:
		currentController.reset(new controller::MainMenuController(*this));
		break;
	default:
		assert(false);
	}
}

void Engine::scheduleEvent(std::string const & event, std::string const & info)
{
	// Main game script
	if (mainScript.hasHandlerForEvent(event)) {
		scheduledTasks.emplace_back(-1, 0, event, info, mainScript);
	}

	// Current map script
	if (mapScript.hasHandlerForEvent(event)) {
		scheduledTasks.emplace_back(0, 0, event, info, mapScript);
	}

	// Extension scripts
	// for (auto const & script : extensionScripts) {
	// 	if (script.hasHandlerForEvent(event)) {
	// 		scheduledTasks.emplace_back(, , event, info, script);
	// 	}
	// }

	// Objects
	// for (auto const & gameObject : gameObjects) {
	// 	if (gameObject.script.hasHandlerForEvent(event)) {
	// 		for (auto const & object : objects) {
	// 			if (object.type == ) {
	// 				scheduledTasks.emplace_back(, , event, info, gameObject.script);
	// 			}
	// 		}
	// 	}
	// }

	// Units

	// Items

	// Infos
}

void Engine::handleScheduledEvent(std::string const &, bool)
{
	// for (auto const & task : scheduledTasks) {
	// 	if (task.event == event) {
	// 		task.script.execute();
	// 	}
	// }

	scheduledTasks.clear();
}
