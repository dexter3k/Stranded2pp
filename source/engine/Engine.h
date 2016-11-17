#pragma once

#include <memory>
#include <iostream>
#include <vector>

class Input;
class Modification;
class Network;
class Sound;

namespace gfx
{
	class Graphics;
	class Color;
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
	Engine(Input& input, gfx::Graphics& graphics, Network& network,
		Sound& sound);
	~Engine();

	bool init(const Modification& modification);
	void update(float deltaTime);

	void setGameState(GameState newGameState);
	GameState getGameState() const;

	void skipIntro();

	void resetGame();
	void setupGame(uint32_t day, uint8_t hour, uint8_t minute,
		bool timeIsFreezed, const std::string& skybox, bool multiplayerMap,
		uint8_t climate, const std::string& music,
		const std::string& briefScript);
	void setupQuickslots(const std::vector<std::string>& quickslots);
	bool setupTerrain(unsigned terrainSize, const std::vector<float>& heightMap,
		unsigned colorMapSize, const std::vector<gfx::Color>& colorMap,
		const std::vector<uint8_t>& grassMap);
private:
	bool loadGame();
private:
	static const unsigned gameTimeRatio; // game minutes / real milliseconds
private:
	Input&		input;
	gfx::Graphics&	graphics;
	Network&	network;
	Sound&		sound;

	GameState gameState;

	std::string modBaseDirectory;

	// Game values

	bool isTimePaused;

	long long timeCounter; // Counts time until it reaches limit (gameTimeRatio)

	unsigned currentDay;
	unsigned dayTime; // in-game time in minutes

	bool timeChanged;
};
