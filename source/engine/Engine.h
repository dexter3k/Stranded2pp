#pragma once

#include <memory>

class Input;
class Modification;
class Network;
class Sound;

namespace gfx
{

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
	Engine(Input& input, gfx::Graphics& graphics, Network& network,
		Sound& sound);
	~Engine();

	bool init(const Modification& modification);
	void update(float deltaTime);

	void setGameState(GameState newGameState);
	GameState getGameState() const;

	void skipIntro();
private:
	Input&		input;
	gfx::Graphics&	graphics;
	Network&	network;
	Sound&		sound;

	GameState gameState;

	std::string modBaseDirectory;
};
