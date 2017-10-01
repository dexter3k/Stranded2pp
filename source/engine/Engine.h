#pragma once

#include <iostream>
#include <vector>

#include "script/ExecutionContext.h"
#include "script/Program.h"

#include "input/Event.h"

class Input;
class Modification;
class Network;
class Sound;
class Stranded;

namespace gfx
{
	class Color;
	class Graphics;
} // namespace gfx

class Engine
{
	enum GameState
	{
		Intro,
		MainMenu,
		Singleplayer,
		Multiplayer,
		Editor
	};
public:
	Engine(Stranded & game, gfx::Graphics & graphics, Network & network,
		Sound & sound, Modification const & modification);

	bool processEvent(Event event);
	void update(double deltaTime);

	void resetGame();
	void setupGame(uint32_t day, uint8_t hour, uint8_t minute,
		bool timeIsFreezed, std::string const & skybox, bool multiplayerMap,
		uint8_t climate, std::string const & music,
		std::string const & briefScript);
	void setupQuickslots(std::vector<std::string> const & quickslots);
	bool setupTerrain(unsigned terrainSize, std::vector<float> const & heightMap,
		unsigned colorMapSize, std::vector<gfx::Color> const & colorMap,
		std::vector<uint8_t> const & grassMap);

	void loadGame(std::string const &) { /* todo */ };
private:
	bool updateTime(double deltaTime);

	bool loadGameConfig();
	bool parseGameConfig(std::string const & filename);
private:
	static const unsigned msPerGameMinute;
private:
	//Stranded & game;

	gfx::Graphics & graphics;
	//Network & network;
	//Sound & sound;

	GameState gameState;

	std::string modBaseDirectory;

	// Script

	// Global execution context (global vars, functions, procedures)
	script::ExecutionContext scriptContext;

	std::string gameScriptSource;

	script::Program mainScript;
	script::Program mapScript;

	// Game values

	bool isTimePaused;

	long long timeCounter; // Counts time until it reaches limit (gameTimeRatio)

	unsigned currentDay;
	unsigned dayTime; // in-game time in minutes

	bool timeChanged;
};
