#pragma once

#include <memory>

class Graphics;
class Gui;
class Input;
class Modification;
class Network;
class Sound;

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
	Engine(const std::shared_ptr<Input>& input,
		const std::shared_ptr<Graphics>& graphics,
		const std::shared_ptr<Gui>& gui,
		const std::shared_ptr<Network>& network,
		const std::shared_ptr<Sound>& sound);
	~Engine();

	bool init(const std::shared_ptr<const Modification>& modification);
	void update(float deltaTime);

	void setGameState(GameState newGameState);
	GameState getGameState() const;
private:
	std::shared_ptr<Input>		input;
	std::shared_ptr<Graphics>	graphics;
	std::shared_ptr<Gui>		gui;
	std::shared_ptr<Network>	network;
	std::shared_ptr<Sound>		sound;

	GameState gameState;
};
