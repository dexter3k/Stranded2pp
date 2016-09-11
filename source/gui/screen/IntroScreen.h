#pragma once

#include "Screen.h"

#include "input/RawInputHandler.h"

class Input;

class IntroScreen : public Screen
{
	typedef Screen super;

	class InputHandler : public RawInputHandler
	{
		typedef RawInputHandler super;
	public:
		InputHandler(Input& input, IntroScreen& introScreen) :
			super(&input),
			introScreen(introScreen)
		{}

		bool onKeyPressed(uint8_t key, bool alt, bool control, bool shift,
			bool super) override;
		bool onMouseButtonPressed(uint8_t button, int x, int y) override;
	private:
		IntroScreen& introScreen;
	};
	friend class InputHandler;
public:
	IntroScreen(Gui& gui, Input& input);
	~IntroScreen();

	void create() override;
	void destroy() override;

	void update(float deltaTime) override;
private:
	void skipIntro();
private:
	std::shared_ptr<InputHandler> inputHandler;
};
