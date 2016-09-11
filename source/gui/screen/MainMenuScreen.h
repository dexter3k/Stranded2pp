#pragma once

#include "Screen.h"

#include "input/RawInputHandler.h"

class Input;

class MainMenuScreen : public Screen
{
	typedef Screen super;

	class InputHandler : public RawInputHandler
	{
		typedef RawInputHandler super;
	public:
		InputHandler(Input& input, MainMenuScreen& mainMenuScreen) :
			super(&input),
			mainMenuScreen(mainMenuScreen)
		{}

		bool onMouseButtonPressed(uint8_t button, int x, int y) override;
	private:
		MainMenuScreen& mainMenuScreen;
	};
	friend class InputHandler;
public:
	MainMenuScreen(Gui& gui, Input& input);
	~MainMenuScreen();

	void create() override;
	void destroy() override;

	void update(float deltaTime) override;
private:
	std::shared_ptr<InputHandler> inputHandler;
};
